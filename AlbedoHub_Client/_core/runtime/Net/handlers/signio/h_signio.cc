#include "h_signio.h"
#include "../../net_context.h"
#include "../../../runtime_events.h"

#include <AlbedoLog.hpp>
#include <AlbedoProtocol.pb.h>
#include <register_protocol.pb.h>
#include <signio_protocol.pb.h>

#include "../../../../global_context.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime{
namespace Handler
{
	
	void HSignIO::handle(std::shared_ptr<net::Envelope> envelope)
	{
		auto& message = envelope->message();
		auto& sender = envelope->sender();
		auto message_id = message.header.message_id;
		log::info("Sign IO Handling {} ", message_id);

		auto& netContext = NetContext::instance();

		if (AlbedoProtocol::SIGNIN_REQUEST == message_id)
		{
			sender->send(message);
		}
		else if (AlbedoProtocol::SIGNIN_SUCCESS == message_id)
		{
			netContext.user_profile = std::make_unique<SignIOProtocol::UserProfile>();
			if (netContext.user_profile->ParseFromString(message.body.message))
			{
				auto& configPath = GlobalContext::instance().g_Albedo_Config_Path;
				std::ifstream file{ configPath };
				if (file.is_open())
				{
					nlohmann::json config = nlohmann::json::parse(file);
					config["Online_UID"] = netContext.user_profile->uid();
					config["Online_Name"] = netContext.user_profile->nickname();
					file.close();

					std::ofstream outfile{ configPath };
					if (outfile.is_open())
					{
						outfile << std::setw(4) << config << std::endl;
						outfile.close();
					}
					else log::error("Failed to save configuration {}", configPath);
				}
				else log::error("Failed to open configuration {}", configPath);


				SignIOEvent::trigger(true, "Welcom to Albedo Hub!");
			}
			else SignIOEvent::trigger(false, "Failed to parse User Profile protobuf!");
		}
		else if (AlbedoProtocol::SIGNIN_FAILED == message_id)
		{
			SignIOEvent::trigger(false, message.body.message);
		}
		else throw std::runtime_error("Failed to handle register! - Unknow Protocol");
	}

}}}}} // namespace Albedo::Hub::Client::Runtime::Handler
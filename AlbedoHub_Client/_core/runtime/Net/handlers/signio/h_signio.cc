#include "h_signio.h"
#include "../../net_context.h"
#include "../../../runtime_events.h"

#include <AlbedoLog.hpp>
#include <AlbedoProtocol.pb.h>
#include <register_protocol.pb.h>
#include <signio_protocol.pb.h>

#include <iostream>

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
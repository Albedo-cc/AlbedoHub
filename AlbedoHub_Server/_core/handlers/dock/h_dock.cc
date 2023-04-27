#include "h_dock.h"

#include <AlbedoProtocol.pb.h>

namespace Albedo {
namespace Hub{
namespace Server{
namespace Handler
{
	
	void HDock::handle(std::shared_ptr<net::Envelope> envelope)
	{
		auto& message = envelope->message();
		auto& user = envelope->sender();
		auto message_id = message.header.message_id;

		if (message_id == AlbedoProtocol::PID::DOCK_SHAKE_HAND)
		{
			DockProtocol::ShakeHand shakeHandInfo{};
			if (!shakeHandInfo.ParseFromString(message.body.message))
			{
				log::warn("Failed to parse a binary protobuf: {}", message.body.message);
				user->send({ AlbedoProtocol::PID::FAILED, "Invalid Protocol Buffers!" });
			}
			else
			{

			}
		}
		else if (message_id == AlbedoProtocol::PID::DOCK_ALIVE)
		{
			log::warn("DOCK_ALIVE need to be implemented!");
		}
		else
		{
			log::warn("Failed to handle a register request, PID: {}", message_id);
			user->send({ AlbedoProtocol::PID::REGISTER_FAILED, "Invalid Protocol ID!" });
		}
	} // void handle(...)

}}}} // namespace Albedo::Hub::Server::Handler
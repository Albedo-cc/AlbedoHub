#include "h_dock.h"
#include "../../net_context.h"
#include "../../../runtime_events.h"

#include <AlbedoLog.hpp>
#include <AlbedoProtocol.pb.h>

#include <iostream>

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime{
namespace Handler
{
	
	void HDock::handle(std::shared_ptr<net::Envelope> envelope)
	{
		auto& message = envelope->message();
		auto& sender = envelope->sender();
		auto message_id = message.header.message_id;
		log::info("Dock Handling {} ", message_id);

		if (message_id == AlbedoProtocol::DOCK_SEND_DOCKERLIST)
		{
			auto newlist = std::make_shared<DockProtocol::DockerList>();
			newlist->ParseFromString(message.body.message);
			NetContext::instance().updateDockerList(newlist);
		}
		else throw std::runtime_error("Failed to handle dock! - Unknow Protocol");
	}

}}}}} // namespace Albedo::Hub::Client::Runtime::Handler
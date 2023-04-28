#pragma once

#include "net_context.h"
#include "handlers/handler_list.h"

namespace Albedo{
namespace Hub{
namespace Client{
namespace Runtime
{
	
	class Net:
		public pattern::Singleton<Net>
	{
		friend class pattern::Singleton<Net>;
	public:
		void update()
		{
			auto& envelopes = context.m_client.getMessageDeque();

			// Handle Reconnect
			context.isOnline = context.m_client.isConnected();
			if (context.tryToConnect && !context.isOnline)
			{
				log::info("Reconnecting");
				reconnect_to_server();
				context.tryToConnect = false;
			}

			// Server Responses
			while (!envelopes.empty()) // Future: Time Limit
			{
				auto envelope = std::make_shared<net::Envelope>(std::move(envelopes.pop_front()));

				if (envelope->message().intact())
				{
					if (false == context.m_handler_pool.handle(envelope))
						log::warn("Failed to handle a message - No suitable handlers for MID {}",
							envelope->message().header.message_id);
				}
				else log::warn("Discarded a non-intact message from server!");
			}
		}

	private:
		Net() :
			context{ NetContext::instance() }
		{
			context.m_client.connect("127.0.0.1", 5200);

			// Register Handlers
			context.m_handler_pool.regist(1, std::make_shared<Handler::HRegister>());
			context.m_handler_pool.regist(10, std::make_shared<Handler::HDock>());
		}

	private:
		NetContext& context;
	private:
		void reconnect_to_server()
		{
			context.m_client.disconnect();
			context.m_client.connect("127.0.0.1", 5200, true);
		}
	};

}}}} // namespace Albedo::Hub::Client::Runtime
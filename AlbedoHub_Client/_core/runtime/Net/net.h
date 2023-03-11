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
			auto& context = NetContext::instance();
			auto& envelopes = m_client.getMessageDeque();

			// Handle Reconnect
			context.isOnline = m_client.isConnected();
			if (context.tryToConnect && !context.isOnline)
			{
				log::info("Reconnecting");
				reconnect_to_server();
				context.tryToConnect = false;
			}

			// Client Requests
			while(!context.m_requests.empty())
			{
				auto& request = context.m_requests.front();
				if (!m_handler_pool.handle(std::make_shared<net::Envelope>(request->message, m_client.getSession())))
				{
					log::warn("Failed to handle message - Unknow MID");
				}
				context.m_requests.pop_front();
			}

			// Server Responses
			while (!envelopes.empty())
			{
				auto envelope = std::make_shared<net::Envelope>(std::move(envelopes.pop_front()));
				auto& message = envelope->message();
				decltype(context.m_feedbacks.find(message.header.message_id)) feedback;
				try
				{
					if (!m_handler_pool.handle(envelope))
						log::warn("Failed to handle a message - No suitable handlers for MID {}",
							message.header.message_id);
				}
				catch (net::HandlerResponse& response)
				{
					feedback = context.m_feedbacks.find(message.header.message_id);
					if (feedback != context.m_feedbacks.end())
					{
						feedback->second->complete = response.isCompleted;
						feedback->second->response = response.response;
						feedback->second.reset();
					}
					else log::info("Handler Response: ({}) {}", response.isCompleted, response.response);
				}
			}
		}

	private:
		Net():
			m_client{},
			m_handler_pool{ [](net::MID mID)->net::HID {return mID / 100; } }
		{
			m_client.connect("127.0.0.1", 5200);

			// Register Handlers
			m_handler_pool.regist(1, std::make_shared<Handler::HRegister>());
		}
	private:
		net::Client m_client;
		net::HandlerPool m_handler_pool;

	private:
		void reconnect_to_server()
		{
			m_client.disconnect();
			m_client.connect("127.0.0.1", 5200, true);
		}
	};

}}}} // namespace Albedo::Hub::Client::Runtime
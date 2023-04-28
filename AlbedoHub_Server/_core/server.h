#pragma once

#define ALBEDONET_SERVER
#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>
#include <AlbedoTime.hpp>
#include <AlbedoProtocol.pb.h>

#include "harbor.h"

#include "server_context.h"
#include "handlers/handler_list.h"

#include "service/mail/mail_service.h"
#include "service/database/database_service.h"

namespace Albedo {
namespace Hub{
namespace Server
{
	constexpr const uint16_t SERVER_PORT = 5200;
	
	class AlbedoHubServer:
		public pattern::Singleton<AlbedoHubServer>,
		public net::BasicServer
	{
		friend class pattern::Singleton<AlbedoHubServer>;

	public:
		void start() // Override
		{
			listen();
			m_context_thread = std::thread([this]() {m_context.run(); });
			auto& context = ServerContext::instance();

			m_periodic_tasks_thread = std::thread([this]() { handle_periodic_tasks(); });
			m_periodic_tasks_thread.detach();

			context.running = true;
			while (context.running) handle();
		}

		virtual void handle(uint32_t limit_message = std::numeric_limits<uint32_t>::max(), bool waitable = true) override
		{
			if (waitable) m_message_in.wait();
			while (!m_message_in.empty() && limit_message--)
			{
				auto envelope = std::make_shared<net::Envelope>(std::move(m_message_in.pop_front()));

				if (envelope->message().intact())
				{
					if (!envelope->sender())
						log::error("NO SENDER!! -- EXPERIED");
					if(!m_handler_pool.handle(envelope))
					{
						envelope->sender()->send({ AlbedoProtocol::PID::FAILED,
						"Failed to handle message - Unknown Protocol" });
					}
				}
				else
				{
					envelope->sender()->send({ AlbedoProtocol::PID::RESEND,
						"Sorry, your message was rejected because it is not intact, please try to resend" });
					log::warn("Received a non-intact message and it has been discarded");
				}
			} // end while
		}
	private:
		net::HandlerPool m_handler_pool;
		std::thread m_periodic_tasks_thread;

	private:
		AlbedoHubServer():
			net::BasicServer{ SERVER_PORT },
			m_handler_pool{ [](net::MID mID)->net::HID { return mID / 100; } }
		{
			log::info("[Albedo Hub Server]: Starting (Port {})", SERVER_PORT);
			// Start Services
			DatabaseService::instance().start();
			MailService::instance().start();
			// Register Handlers
			m_handler_pool.regist(1, std::make_shared<Handler::HRegister>());
			m_handler_pool.regist(10, std::make_shared<Handler::HDock>());
		}
		~AlbedoHubServer() 
		{
			log::info("[Albedo Hub Server]: Closing");
		}

	private:
		void handle_periodic_tasks()
		{
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));

				constexpr float PERIOD_DOCKERLIST = 2.0;
				static float period_dockerlist_sync = PERIOD_DOCKERLIST;
				period_dockerlist_sync -= 1.0;
				{
					if (period_dockerlist_sync < 0)
					{
						period_dockerlist_sync = PERIOD_DOCKERLIST;

						const auto& strDockerlist = Harbor::instance().MakeDockerListString();

						if (!strDockerlist.empty())
						{
							log::info("Synchronizing Dock List!");
							Message docklist{AlbedoProtocol::DOCK_SEND_DOCKERLIST, strDockerlist };
							sendToAll(docklist);
						}
					}
				} // dockerlist task

			} // end while
			
		}

	};

}}} // namespace Albedo::Hub::Server
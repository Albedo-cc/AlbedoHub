#pragma once

#define ALBEDONET_SERVER
#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>
#include <AlbedoProtocol.pb.h>

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
		public net::Server
	{
		friend class pattern::Singleton<AlbedoHubServer>;

	public:
		void start() // Override
		{
			listen();
			m_context_thread = std::thread([this]() {m_context.run(); });
			auto& context = ServerContext::instance();
			context.running = true;
			while (context.running) handle();
		}

		virtual void handle(uint32_t limit_message = std::numeric_limits<uint32_t>::max(), bool waitable = true) override
		{
			if (waitable) m_message_in.wait();
			while (!m_message_in.empty() && limit_message--)
			{
				auto&& envelope = std::move(m_message_in.pop_front());
				if (envelope.message().intact())
				{
					auto pMessage = std::make_shared<net::Envelope>(envelope);
					if(m_handler_pool.handle(std::move(pMessage)))
						envelope.sender()->send({ AlbedoProtocol::PID::SUCCESS });
					else
					{
						envelope.sender()->send({ AlbedoProtocol::PID::FAILED,
						"Failed to handle message - Unknown Protocol" });
					}
				}
				else
				{
					envelope.sender()->send({ AlbedoProtocol::PID::RESEND,
						"Sorry, your message was rejected because it is not intact, please try to resend" });
					log::warn("Received a non-intact message and it has been discarded");
				}
			} // end while
		}
	private:
		net::HandlerPool m_handler_pool;
	private:
		AlbedoHubServer():
			net::Server{ SERVER_PORT },
			m_handler_pool{ [](net::MID mID)->net::HID { return mID / 100; } }
		{
			log::info("[Albedo Hub Server]: Starting (Port {})", SERVER_PORT);
			// Start Services
			DatabaseService::instance().start();
			MailService::instance().start();
			// Register Handlers
			m_handler_pool.regist(1, std::make_shared<Handler::HRegister>());
		}
		~AlbedoHubServer() 
		{
			log::info("[Albedo Hub Server]: Closing");
		}
	};

}}} // namespace Albedo::Hub::Server
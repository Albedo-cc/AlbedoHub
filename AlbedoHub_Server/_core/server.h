#pragma once

#define ALBEDONET_SERVER
#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>

#include "handlers/handler_pool.h"
#include "handlers/handler_list.h"

namespace Albedo {
namespace Hub{
namespace server
{
	constexpr const uint16_t SERVER_PORT = 5200;
	
	class AlbedoHubServer:
		public pattern::Singleton<AlbedoHubServer>,
		public net::Server
	{
		friend class pattern::Singleton<AlbedoHubServer>;

	public:
		virtual void handle(uint32_t limit_message = std::numeric_limits<uint32_t>::max(), bool waitable = true) override
		{
			m_message_in.wait();
			auto message = std::make_shared<net::SignedMessage>(std::move(m_message_in.pop_front()));
			m_handler_pool->handle(std::move(message));
		}
	private:
		std::unique_ptr<handler::HandlerPool> m_handler_pool;
	private:
		AlbedoHubServer():
			net::Server{ SERVER_PORT },
			m_handler_pool{std::make_unique<handler::HandlerPool>()}
		{
			log::info("[Albedo Hub Server]: Starting (Port {})", SERVER_PORT);
			// Services
			service::MailService::instance().start();
			// Handlers
			m_handler_pool->regist(Message::REGISTER, std::make_shared<handler::HRegister>());
		}
		~AlbedoHubServer() 
		{
			log::info("[Albedo Hub Server]: Closing");
		}
	};

}}} // namespace Albedo::Hub::server
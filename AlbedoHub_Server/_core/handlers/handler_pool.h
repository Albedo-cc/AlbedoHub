#pragma once

#include <AlbedoLog.hpp>
#include <AlbedoNet.hpp>
#include <memory>
#include <unordered_map>

#include <message.pb.h>

namespace Albedo {
namespace Hub{
namespace server{
namespace handler
{
	
	class Handler
	{
	public:
		virtual void handle(std::shared_ptr<net::SignedMessage> message) = 0;
	};

	class HandlerPool
		:public net::uncopyable
	{
	public:
		HandlerPool() = default;

		void handle(std::shared_ptr<net::SignedMessage> signedMessage)
		{
			if (!signedMessage->intact()) // Future: Request Resend
				log::warn("Received a non-intact message!");

			log::info("\n MID {} \n Body: {}\n", signedMessage->header.message_id, signedMessage->body.message);

			auto handler = m_handlers.find(static_cast<Message::Type>(signedMessage->header.message_id));
			if (handler == m_handlers.end())
			{
				// Not throw exception to interrupt the server
				log::warn("Failed to handle message - Unknow type {}", signedMessage->header.message_id);
			}
			else handler->second->handle(std::move(signedMessage));
		}

		void regist(Message::Type message_type, std::shared_ptr<Handler> handler)
		{
			m_handlers.emplace(message_type, std::move(handler));
		}

		std::shared_ptr<Handler> getHandler(Message::Type message_type)
		{
			auto handler = m_handlers.find(message_type);
			if (handler == m_handlers.end())
			{
				// Not throw exception to interrupt the server
				log::warn("Failed to get handler - Unknow type {}", message_type);
			}
			else return handler->second;
		}
	private:
		std::unordered_map<Message::Type, std::shared_ptr<Handler>> m_handlers;
	};

}}}} // namespace Albedo::Hub::server::handler
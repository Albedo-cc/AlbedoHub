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
	{
	public:
		void handle(Message::Type type, std::shared_ptr<net::SignedMessage> message)
		{
			auto handler = m_handlers.find(type);
			if (handler == m_handlers.end())
			{
				// Not throw exception to interrupt the server
				log::warn("Failed to handle message - Unknow type {}", type);
			}
			else handler->second->handle(std::move(message));
		}
	private:
		std::unordered_map<Message::Type, std::unique_ptr<Handler>> m_handlers;
	};

}}}} // namespace Albedo::Hub::server::handler
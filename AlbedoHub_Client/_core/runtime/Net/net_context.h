#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>
#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>

#include <memory>

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{
	class NetContext:
		public pattern::Singleton<NetContext>
	{
		friend class pattern::Singleton<NetContext>;
		friend class Net;
	public:
		bool tryToConnect = false;
		bool isOnline = false;

		void sendMessage(net::Message message)
		{
			auto envelope = std::make_shared<net::Envelope>(message, m_client.getSession());
			m_handler_pool.handle(envelope);
		}

	private:
		net::BasicClient m_client;
		net::HandlerPool m_handler_pool;
	private:
		NetContext() : m_handler_pool{ [](net::MID mID)->net::HID {return mID / 100; } } {}
	};

}}}} // namespace Albedo::Hub::Client::Runtime
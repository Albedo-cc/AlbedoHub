#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>
#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>

#include <memory>

// Protocols
#include <dock_protocol.pb.h>

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

		std::shared_ptr<DockProtocol::DockerList> getDockList() { return m_dockerlist; }

		void updateDockerList(std::shared_ptr<DockProtocol::DockerList> newlist)
		{
			m_dockerlist.swap(newlist);
		}

		void setSelectedDocker(std::string_view address, int32_t port)
		{
			m_selected_docker_address = address;
			m_selected_docker_port = port;
		}

		void getSelectedDocker(std::string& address, int32_t& port)
		{
			address = m_selected_docker_address;
			port = m_selected_docker_port;
		}

	private:
		net::BasicClient m_client;
		net::HandlerPool m_handler_pool;
		std::shared_ptr<DockProtocol::DockerList> m_dockerlist;

		std::string_view m_selected_docker_address;
		int32_t m_selected_docker_port;

	private:
		NetContext() : 
			m_handler_pool{ [](net::MID mID)->net::HID {return mID / 100; } },
			m_dockerlist{ std::make_shared<DockProtocol::DockerList>() }
		{}
	};

}}}} // namespace Albedo::Hub::Client::Runtime
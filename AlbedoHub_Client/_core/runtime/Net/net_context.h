#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>
#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>

#include <memory>

// Protocols
#include <dock_protocol.pb.h>
#include <signio_protocol.pb.h>

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
		bool hasSignedIn = false;

		std::unique_ptr<SignIOProtocol::UserProfile> user_profile;

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

		void setSelectedDocker(const DockProtocol::ShakeHand* docker)
		{
			m_selected_docker = docker;
		}

		const DockProtocol::ShakeHand* getSelectedDocker()
		{
			return m_selected_docker;
		}

	private:
		net::BasicClient m_client;
		net::HandlerPool m_handler_pool;
		std::shared_ptr<DockProtocol::DockerList> m_dockerlist;

		const DockProtocol::ShakeHand* m_selected_docker;

	private:
		NetContext() : 
			m_handler_pool{ [](net::MID mID)->net::HID {return mID / 100; } },
			m_dockerlist{ std::make_shared<DockProtocol::DockerList>() }
		{}
	};

}}}} // namespace Albedo::Hub::Client::Runtime
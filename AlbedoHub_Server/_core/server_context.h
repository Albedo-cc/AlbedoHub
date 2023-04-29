#pragma once

#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

#include <memory>
#include <unordered_set>

namespace Albedo {
namespace Hub{
namespace Server
{
	
	class ServerContext:
		public pattern::Singleton<ServerContext>
	{
		friend class pattern::Singleton<ServerContext>;
		friend class AlbedoHubServer;

	private:
		bool running = false;

	public:
		void shutdown(const char* caller_signature)
		{
			running = false;
			log::critical("{} shutdowned the server!", caller_signature);
		}

		void AddOnlineUser(net::SPSession user_session)
		{
			if (m_online_users.find(user_session) == m_online_users.end())
				m_online_users.emplace(std::move(user_session));
			else log::warn("Failed to add an online user!");
		}

		void RemoveOnlineUser(net::SPSession user_session)
		{
			if (m_online_users.find(user_session) != m_online_users.end())
				m_online_users.erase(user_session);
			else log::warn("Failed to remove an unexistent online user!");
		}

	private:
		std::unordered_set<net::SPSession> m_online_users; // Signed In

	private:
		ServerContext() = default;
	};

}}}
#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

#include <memory>
#include <source_location>

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
	private:
		ServerContext() = default;
	};

}}}
#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

namespace Albedo {
namespace Hub{
namespace client
{
	
	class AlbedoHubContext:
		public pattern::Singleton<AlbedoHubContext>
	{
		friend class pattern::Singleton<AlbedoHubContext>;
		friend class AlbedoHub;

	private:
		bool running = false;

	public:
		void shutdown(const char* caller_signature)
		{
			running = false;
			log::critical("{} shutdowned Albedo Hub!", caller_signature);
		}
	private:
		AlbedoHubContext() = default;
	};

}}} // namespace Albedo::Hub::client
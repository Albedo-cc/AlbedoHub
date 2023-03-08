#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

#include "client_context.h"
#include "Net/net_layer.h"

namespace Albedo {
namespace Hub{
namespace client
{
	
	class AlbedoHub:
		public pattern::Singleton<AlbedoHub>
	{
		friend class pattern::Singleton<AlbedoHub>;
	public:
		void start()
		{
			auto& context = AlbedoHubContext::instance(); 
			context.running = true;
			while (context.running)
			{
				NetLayer::instance().update();
			}
		}
	private:
		AlbedoHub()
		{
			log::info("Albedo Hub started.");
		}
		~AlbedoHub()
		{
			log::info("Albedo Hub is closing.");
		}
	};

}}} // namespace Albedo::Hub::client
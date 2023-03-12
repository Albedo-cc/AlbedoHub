#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

#include "global_context.h"
#include "runtime/Net/net.h"
#include "runtime/UI/ui.h"

namespace Albedo {
namespace Hub{
namespace Client
{
	
	class AlbedoHub:
		public pattern::Singleton<AlbedoHub>
	{
		friend class pattern::Singleton<AlbedoHub>;
	public:
		void start()
		{
			auto& context = GlobalContext::instance();
			auto& layer_net = Runtime::Net::instance(); // Bind Context
			auto& layer_UI = Runtime::UI::instance(); // Bind Context
			context.m_running = true;
			while (context.isRunning())
			{
				layer_net.update();
				layer_UI.update();
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

}}} // namespace Albedo::Hub::Client
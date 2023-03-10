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
			context.m_running = true;
			while (context.isRunning())
			{
				//Runtime::Net::instance().update();
				Runtime::UI::instance().update();
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
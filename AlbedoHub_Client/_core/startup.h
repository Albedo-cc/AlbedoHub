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
			//system(R"("C:\Frozen Zone\MyGitHub\AlbedoHub\build\AlbedoHub_Client\_core\Debug\Albedo.lnk" 10000007 Frozen 127.0.0.1 5201 57B0C4D90311C6F08B8D419536474E0EFEABF50CA97782E7051BEA5658E17E6C)");
			
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
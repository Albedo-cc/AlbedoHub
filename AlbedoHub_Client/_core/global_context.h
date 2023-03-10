#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

#include "runtime/Net/net_context.h"
#include "runtime/UI/UI_context.h"

namespace Albedo{
namespace Hub{
namespace Client
{
	
	class GlobalContext:
		public pattern::Singleton<GlobalContext>
	{
		friend class pattern::Singleton<GlobalContext>;
		friend class AlbedoHub;

	public: // All Runtime Context
		UIContext& g_context_UI;

	public:
		bool isRunning() const { return m_running; }

		void shutdown(const char* caller_signature)
		{
			m_running = false;
			log::critical("{} shutdowned Albedo Hub!", caller_signature);
		}
		
	private:
		GlobalContext():
			g_context_UI{UIContext::instance()}
		{

		}
		bool m_running = false;
	};

}}} // namespace Albedo::Hub::Client
#pragma once

#include <AlbedoPattern.hpp>
#include <AlbedoTime.hpp>
#include <AlbedoLog.hpp>

#include "runtime/Net/net_context.h"
#include "runtime/UI/UI_context.h"

#include <fstream>
#include <json.hpp>

namespace Albedo{
namespace Hub{
namespace Client
{
	
	class GlobalContext:
		public pattern::Singleton<GlobalContext>
	{
		friend class pattern::Singleton<GlobalContext>;
		friend class AlbedoHub;

	public: 
		// All Runtime Context
		Runtime::NetContext& g_context_Net;
		Runtime::UIContext& g_context_UI;
		std::string g_Albedo_Path;
		std::string g_Albedo_Config_Path;

	public:
		bool isRunning() const { return m_running; }

		void shutdown(const char* caller_signature)
		{
			m_running = false;
			log::critical("{} shutdowned Albedo Hub!", caller_signature);
		}

		void SystemCall(std::string_view command)
		{
			log::warn("System Call: {}", command);
			system(command.data());
		}
		
	private:
		GlobalContext() :
			g_context_Net{ Runtime::NetContext::instance() },
			g_context_UI{ Runtime::UIContext::instance() }
		{
			g_Albedo_Path = R"(Albedo.lnk)";
			g_Albedo_Path.resize(128);

			g_Albedo_Config_Path = R"(C:\Frozen Zone\MyGitHub\Albedo\build\Albedo\Debug\config.json)";
			g_Albedo_Config_Path.resize(128);
		}
		bool m_running = false;
	};

}}} // namespace Albedo::Hub::Client
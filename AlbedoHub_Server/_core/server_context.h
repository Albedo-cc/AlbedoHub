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

}}} // namespace Albedo::Hub::Server

//
////AuthenTable::insert("745574309@qq.com", net::Hash::SHA256("123321"));
//
//auto p = AuthenTable::search("Account = '745574309@qq.com' ");
//auto result = p->get_result();
//if (!result || result->empty()) log::error("Result empty!");
//else
//{
//	auto user = result->fetch_first();
//	if (user.empty()) log::error("Result empty!");
//	else log::info("UID:{}\nAccount:{}\nPassword:{}", user["UID"], user["Account"], user["Password"]);
//}
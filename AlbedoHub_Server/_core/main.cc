#include <AlbedoLog.hpp>

#include "server.h"

int main(int argc, char* argv[])
{
	using namespace Albedo;
	using namespace Albedo::Hub::server;
	try
	{
		AlbedoHubServer::instance().start();
	}
	catch (std::runtime_error& e)
	{
		log::error("[Albedo Hub Server (Unsolved Exception)]: {}", e.what());
	}
	return 0;
}
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
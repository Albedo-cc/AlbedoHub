#include <AlbedoLog.hpp>

#include "server.h"

int main(int argc, char* argv[])
{
	using namespace Albedo;
	using namespace Albedo::Hub::Server;
	try
	{
		AlbedoHubServer::instance().start();
	}
	catch (std::exception& e)
	{
		log::error("[Albedo Hub Server (Unsolved Exception)]: {}", e.what());
	}
	return 0;
}

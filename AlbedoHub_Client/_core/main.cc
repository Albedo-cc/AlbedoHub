#include <AlbedoLog.hpp>

#include "albedo_hub.h"

int main(int argc, char* argv[])
{
	using namespace Albedo;
	using namespace Albedo::Hub::client;
	try
	{
		AlbedoHub::instance().start();
	}
	catch (std::exception& e)
	{
		log::error("[Albedo Hub Client (Unsolved Exception)]: {}", e.what());
	}
	return 0;
}
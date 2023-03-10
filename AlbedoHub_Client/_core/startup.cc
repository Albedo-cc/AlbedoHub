#include <AlbedoLog.hpp>

#include "startup.h"

int main(int argc, char* argv[])
{
	using namespace Albedo;
	try
	{
		Albedo::Hub::Client::AlbedoHub::instance().start();
	}
	catch (std::exception& e)
	{
		log::error("[Albedo Hub Client (Unsolved Exception)]: {}", e.what());
	}
	return 0;
}
#include <AlbedoLog.hpp>
#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>

int main(int argc, char* argv[])
{
	using namespace Albedo;
	net::Client client{};
	log::info("Client: Hello World");

	return 0;
}
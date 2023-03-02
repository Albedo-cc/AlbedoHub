#include <AlbedoLog.hpp>
#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>

#include <message.pb.h>
#include <register.pb.h>

int main(int argc, char* argv[])
{
	using namespace Albedo;
	try
	{
		net::Client client{};
		log::info("Client: Hello World");
		client.connect("127.0.0.1", 5200);
		std::string _input;
		_input.reserve(100);
		while (true)
		{
			net::MID _MID;
			std::cout << "\nMessageType :";
			std::cin >> _MID;
			Message::Type::REGISTER;
			std::cout << "\nInput :";
			std::cin >> _input;

			client.sendToServer({ _MID,  _input });
			auto& res = client.getMessages();
			if (res.size()) log::info("Client received {} message(s)!", res.size());
		}
	}
	catch (std::runtime_error& e)
	{
		log::error("[Albedo Hub Client] >> {}", e.what());
	}
	

	return 0;
}
#pragma once

#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>
#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>

#include "handlers/handler_list.h"
#include "net_layer_context.h"

#include <memory>
#include <numeric>

//Temp
#include <AlbedoProtocol.pb.h>
#include <register_protocol.pb.h>


namespace Albedo {
namespace Hub{
namespace client{
namespace layer
{
	
	class Net:
		public pattern::Singleton<Net>
	{
		friend class pattern::Singleton<Net>;
	public:
		void update()
		{
			//// Temp
			//static bool bRegisted = false;
			//if (!bRegisted)
			//{
			//	bRegisted = true;
			//	RegisterProtocol::UserInfo user; // Remeber to delete #include<>
			//	std::string buffer;
			//	std::cout << "[ EMail ] >> ";
			//	std::cin >> buffer;
			//	user.set_account(buffer);
			//	std::cout << "[ Name ] >> "; // 暂时不支持汉字，不能直接使用Protobuf
			//	std::cin >> buffer;
			//	user.set_name(buffer);
			//	std::cout << "[ Password ] >> ";
			//	std::cin >> buffer;
			//	user.set_password(net::Hash::SHA256(buffer));
			//	buffer = user.SerializeAsString();
			//	m_client->sendToServer(
			//		{ AlbedoProtocol::PID::REGISTER_CLIENT_SEND_REQUEST,
			//		buffer });
			//}
		}
	private:
		std::unique_ptr<net::Client> m_client;
		net::HandlerPool m_handler_pool;
	private:
		Net() :
			m_client{ std::make_unique<net::Client>() },
			m_handler_pool{ [](net::MID pid)->net::HID { return pid / 100; }}
		{
			register_handlers();
			connect_to_server();

			std::thread thread_message_handler = std::thread([this]()
				{
					static auto& messages = m_client->getMessageDeque();
					try
					{
						messages.wait();
						while (!messages.empty())
						{
							auto message = std::make_shared<net::SignedMessage>(std::move(messages.pop_front()));
							message->setSender(m_client->getSession());
							m_handler_pool.handle(std::move(message));
						}
					}
					catch (std::exception& e)
					{
						log::error("[Albedo Hub NetLayer - Message Handler]: (Unsoloved exception) {}", e.what());
					}
				});
			thread_message_handler.detach();
		}

		// Helpers
		void register_handlers()
		{
			m_handler_pool.regist(1, std::make_shared<layer::HRegister>());
		}
		void connect_to_server()
		{
			m_client->connect("127.0.0.1", 5200);
			if (!m_client->isConnected())
				throw std::runtime_error("Failed to connect to the server!");
		}
	};

}}}} // namespace Albedo::Hub::client::layer
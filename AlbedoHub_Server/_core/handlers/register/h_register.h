#pragma once

#include "../../service/mail/mail_service.h"

#include <AlbedoNet.hpp>
#include <register_protocol.pb.h>

#include <unordered_map>
#include <memory>
#include <random>
#include <chrono>
#include <string>

namespace Albedo {
namespace Hub{
namespace Server{
namespace Handler
{
	
	class HRegister
		:public net::Handler
	{
		using User = net::SPSession;
		struct RegisterInfo
		{
			RegisterProtocol::UserInfo userinfo;
			std::string vcode;
		};
	public:
		virtual void handle(std::shared_ptr<net::Envelope> message) override;
	private:
		std::unordered_map<User, RegisterInfo> m_verifying_users;

	private:
		std::string generate_vcode()
		{
			static std::random_device seed;
			static std::default_random_engine engine{ seed() };
			static std::uniform_int_distribution dist{100000, 999999};
			return std::to_string(dist(engine));
		}
	};

}}}} // namespace Albedo::Hub::Server::Handler
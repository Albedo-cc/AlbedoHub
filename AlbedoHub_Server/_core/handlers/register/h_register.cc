#include "h_register.h"
#include "register_mail.h"
#include "../../service/database/tables/user.h"
#include <AlbedoProtocol.pb.h>

#include <chrono>

namespace Albedo {
namespace Hub{
namespace Server{
namespace Handler
{
	
	void HRegister::handle(std::shared_ptr<net::Envelope> envelope)
	{
		auto& message = envelope->message();
		auto& user = envelope->sender();
		auto message_id = message.header.message_id;

		if (message_id == AlbedoProtocol::PID::REGISTER_CLIENT_SEND_REQUEST)
		{
			RegisterProtocol::UserInfo userinfo;
			if (!userinfo.ParseFromString(message.body.message))
			{
				log::warn("Failed to parse a binary protobuf: {}", message.body.message);
				user->send({ AlbedoProtocol::PID::REGISTER_FAILED, "Invalid Protocol Buffers!" });
			}
			else //  Send Verification Code
			{
				auto res = Database::UserTable::search_account(userinfo.account());
				int i = 0;
				for (; !res->isExecuted() && i < 100; ++i)
					std::this_thread::sleep_for(std::chrono::microseconds(1));
				if (res->isExecuted())
				{
					if (!res->getResult()->get_result()->empty())
					{
						user->send({ AlbedoProtocol::PID::REGISTER_FAILED,
						"Sorry, account already exists" });
						return;
					}
				} else {
					if (!res->cancel()) log::warn("Failed to cancel the SQL: {}", res->getSQL());
					user->send({ AlbedoProtocol::PID::REGISTER_FAILED,
					"Sorry, database requested time out! Please retry later." });
					return;
				}
				
				log::info("A new user named {} is registing! (Request Time: {}ms)", userinfo.name(), i);

				register_mail::set_name(userinfo.name());
				RegisterProtocol::Verification vcode;
				vcode.set_verification_code(generate_vcode());
				register_mail::set_vcode(vcode.verification_code());
				net::Mail mail
				{
					"Albedo Hub <hub@albedo.cc>",
					{userinfo.account()},
					"[Albedo Hub] Your Verification Code",
					register_mail::get()
				};
				
				MailService::instance().post(std::make_shared<net::Mail>(std::move(mail)));
				user->send({ AlbedoProtocol::PID::REGISTER_SUCCESS,
					"Please send your verification code" });
				
				m_verifying_users.emplace(
					std::move(user),
					RegisterInfo{ std::move(userinfo), vcode.verification_code() });
			}
		}
		else if (message_id == AlbedoProtocol::PID::REGISTER_CLIENT_SEND_VERIFICATION)
		{
			RegisterProtocol::Verification vcode;
			if (!vcode.ParseFromString(message.body.message))
			{
				log::warn("Failed to parse a binary protobuf: {}", message.body.message);
				user->send({ AlbedoProtocol::PID::REGISTER_FAILED, "Invalid Protocol Buffers!" });
			}
			else // Verify
			{
				auto verification_info = m_verifying_users.find(user);
				if (verification_info == m_verifying_users.end())
				{
					log::warn("Failed to verify a invalid user");
					user->send({ AlbedoProtocol::PID::REGISTER_FAILED,
						"Registration is rejected because  your socket may be changed or last register failed!" });
				}
				else
				{
					if (verification_info->second.vcode == vcode.verification_code())
					{
						log::info("User Register Successfully!");
						auto& _userinfo = verification_info->second.userinfo;
						Database::UserTable::insert(_userinfo.account(), _userinfo.password(), _userinfo.name());
						user->send({ AlbedoProtocol::PID::REGISTER_SUCCESS, "Register Successfully!" });
					}
					else {
						log::info("User Register Failed!");
						user->send({ AlbedoProtocol::PID::REGISTER_FAILED, "Register Failed! Please request verificaition code again!" });
					}
					m_verifying_users.erase(user); // Future: save unverified user in the database
				}
			} // End Verify
		}
		else
		{
			log::warn("Failed to handle a register request, PID: {}", message_id);
			user->send({ AlbedoProtocol::PID::REGISTER_FAILED, "Invalid Protocol ID!" });
		}
	} // void handle(...)

}}}} // namespace Albedo::Hub::Server::Handler
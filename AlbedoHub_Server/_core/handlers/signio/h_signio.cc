#include "h_signio.h"

#include "../../service/database/tables/user.h"
#include <AlbedoProtocol.pb.h>
#include <server_context.h>

namespace Albedo {
namespace Hub{
namespace Server{
namespace Handler
{
	
	void HSignIO::handle(std::shared_ptr<net::Envelope> envelope)
	{
		auto& message = envelope->message();
		auto& user = envelope->sender();
		auto message_id = message.header.message_id;

		if (AlbedoProtocol::PID::SIGNIN_REQUEST == message_id)
		{
			SignIOProtocol::SignInInfo signInfo;
			if (signInfo.ParseFromString(message.body.message))
			{
				auto res = Database::UserTable::search_account(signInfo.account());
				int i = 0;
				for (; !res->isExecuted() && i < 100; ++i)
					std::this_thread::sleep_for(std::chrono::microseconds(1));
				if (res->isExecuted())
				{
					auto result = res->getResult()->get_result();
					if (!result->empty())
					{
						auto target = result->fetch_first();
						if (target["Password"] == signInfo.password())
						{
							log::info("{} signed in (Sign In Time: {}ms)", signInfo.account(), i);
							SignIOProtocol::UserProfile profile;
							profile.set_uid(atoi(target["UID"].c_str()));
							profile.set_nickname(target["Name"]);
							user->send({ AlbedoProtocol::PID::SIGNIN_SUCCESS, profile.SerializeAsString()});

							ServerContext::instance().AddOnlineUser(user);
							Database::UserTable::update_login_time(signInfo.account());
						}
						else user->send({ AlbedoProtocol::PID::SIGNIN_FAILED, "Wrong Password!" });
					}
					else user->send({ AlbedoProtocol::PID::SIGNIN_FAILED, "Not found this account." });
				}
				else {
					if (!res->cancel()) log::warn("Failed to cancel the SQL: {}", res->getSQL());
					user->send({ AlbedoProtocol::PID::SIGNIN_FAILED,
					"Sorry, database requested time out! Please retry later." });
					return;
				}
			}
			else log::warn("Failed to parse a Sign In protobuf!");
		}
		else
		{
			log::warn("Failed to handle a register request, PID: {}", message_id);
			user->send({ AlbedoProtocol::PID::REGISTER_FAILED, "Invalid Protocol ID!" });
		}
	} // void handle(...)

}}}} // namespace Albedo::Hub::Server::Handler
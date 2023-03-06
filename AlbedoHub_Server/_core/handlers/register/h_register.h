#pragma once

#include "../handler_pool.h"
#include "../../service/mail/mail_service.h"
#include "mail.h"

#include <unordered_map>
#include <memory>

namespace Albedo {
namespace Hub{
namespace server{
namespace handler
{
	
	class HRegister
		:public Handler
	{
		using VCode = std::string;
		using Memo = std::unordered_map<std::shared_ptr<net::Session>, VCode>;
	public:
		virtual void handle(std::shared_ptr<net::SignedMessage> message) override
		{
			auto user = message->getSender();
			auto memo = m_memo.find(user);
			if (memo == m_memo.end())
			{
				log::info("A new user is registing!");
				user->send({ 1, "Please send your verification code" });
				register_mail::set_name(u8"½­°Ë");
				register_mail::set_vcode("123321");
				net::Mail mail
				{
					"Albedo Hub <hub@albedo.cc>",
					{"745574309@qq.com"},
					"[Albedo Hub] Your Verification Code",
					register_mail::get()
				};
				m_mail_box->push_back(std::make_shared<net::Mail>(std::move(mail)));
				m_memo.emplace(std::move(user), "123321");
			}
			else
			{
				if (memo->second == message->body.message)
				{
					log::info("Register Successfully!");
					memo->first->send({ 1, "Register Successfully!" });
				}
			}
		}
	private:
		Memo m_memo;
		std::shared_ptr<service::MailBox> m_mail_box = service::MailService::instance().getMailBox();
	};

}}}} // namespace Albedo::Hub::server::handler
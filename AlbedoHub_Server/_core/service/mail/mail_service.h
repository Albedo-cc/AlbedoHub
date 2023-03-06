#pragma once

#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>

#include <thread>
#include <memory>
#include <exception>

namespace Albedo {
namespace Hub{
namespace server{
namespace service
{
	using namespace Albedo::net;
	using MailBox = SafeDeque<std::shared_ptr<Mail>>;

	class MailService
		:public pattern::Singleton<MailService>
	{
		friend class pattern::Singleton<MailService>;
	public:
		void start();
		std::shared_ptr<MailBox> getMailBox() 
		{ 
			if (!hasStarted) 
				throw std::runtime_error("Mail Service did not start, so it is invalied to get a mailbox");
			return m_mailbox; 
		}

		const std::thread::id getThreadID() const { return m_thread->get_id(); }
	private:
		MailService() = default;
		~MailService();
		bool hasStarted = false;
		std::unique_ptr<std::thread> m_thread;
		std::shared_ptr<MailBox> m_mailbox;
		SMTP m_smtp{ "hub@albedo.cc" , "@albedo741", "smtps://smtpout.secureserver.net", 465 };
	};

}}}} // namespace Albedo::Hub::server::service
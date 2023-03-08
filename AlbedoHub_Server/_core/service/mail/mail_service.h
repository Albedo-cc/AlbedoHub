#pragma once

#include <AlbedoNet.hpp>
#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>

#include <thread>
#include <memory>
#include <exception>
#include <mutex>

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
		void post(std::shared_ptr<Mail> mail)
		{
			m_mailbox_in->push_back(mail);
		}

		std::shared_ptr<MailBox> getMailBox() 
		{ 
			if (!hasStarted) 
				throw std::runtime_error("Mail Service did not start, so it is invalied to get a mailbox");
			return m_mailbox_in;
		}

		const std::thread::id getThreadID() const { return m_thread->get_id(); }
	private:
		MailService():
			m_mailbox{ std::make_shared<MailBox>() },
			m_mailbox_in{ std::make_shared<MailBox>() }
		{

		}
		~MailService()
		{
			log::info("Mail Service is closing.");
			size_t lost_mails = m_mailbox->size() + m_mailbox_in->size();
			if (lost_mails) log::critical("You have {} unsent mail(s)!", lost_mails);
		}
		bool hasStarted = false;
		std::unique_ptr<std::thread> m_thread;

		std::shared_ptr<MailBox> m_mailbox;
		std::shared_ptr<MailBox> m_mailbox_in;
		SMTP m_smtp{ "hub@albedo.cc" , "@albedo741", "smtps://smtpout.secureserver.net", 465 };

	private:
		void swap_mailbox()
		{
			std::scoped_lock guard{ m_mailbox->get_mutex(), m_mailbox_in->get_mutex() };
			m_mailbox.swap(m_mailbox_in);
		}
	};

}}}} // namespace Albedo::Hub::server::service
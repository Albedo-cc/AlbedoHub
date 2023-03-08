#include "mail_service.h"

namespace Albedo {
namespace Hub{
namespace server{
namespace service
{

	void MailService::start()
	{
		if (hasStarted) return;
		else hasStarted = true;
		try
		{
			m_thread = std::make_unique<std::thread>(
				[this]() // Begin Handling Mails
				{
					while (true)
					{
						try
						{
							m_mailbox_in->wait();
							swap_mailbox();
							while (!m_mailbox->empty())
							{
								auto mail = m_mailbox->pop_front();
								for (int resend = 1; resend <= 2; ++resend)
								{
									if (m_smtp.send(mail)) break;
									else log::warn("Failed to send mail (Retry: {}/2)", resend);
								}
							}
						}
						catch (std::exception& e)
						{
							log::warn("[Albedo Hub Server - MailService]: (Unsoloved exception) {}", e.what());
						}
					}
				}); // End
			m_thread->detach(); // Daemon Thread
		}
		catch (std::exception& e)
		{
			log::error("[Albedo Hub Server - Mail Service]: {}", e.what());
		}

		log::info("[Albedo Hub Server]: Mail Service Started!");
	}

}}}} // namespace Albedo::Hub::server::service
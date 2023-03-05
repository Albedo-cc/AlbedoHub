#include "mail_service.h"

#include <AlbedoLog.hpp>

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
			m_mailbox = std::make_shared<MailBox>();

			m_thread = std::make_unique<std::thread>(
				[&]() // Begin Handling Mails
				{
					while (true)
					{
						m_mailbox->wait();
						m_smtp.send(m_mailbox->pop_front());
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

	MailService::~MailService()
	{
		log::info("MailService Closed!");
	}

}}}} // namespace Albedo::Hub::server::service
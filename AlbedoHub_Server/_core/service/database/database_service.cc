#include "database_service.h"

#include <thread>

namespace Albedo{
namespace Hub{
namespace server{
namespace service
{
	
	void DatabaseService::start()
	{
		if (hasStarted) return;
		else hasStarted = true;
		try
		{
			m_thread = std::make_unique<std::thread>(
				[this]() // Begin Handling SQLs
				{
					while (true)
					{
						m_sql_deque_in->wait();
						swap_SQLPool();
						try
						{
							while (!m_sql_deque->empty())
							{
								auto sql = m_sql_deque->pop_front();
								sql->execute();
							}
						}
						catch (std::exception& e)
						{
							log::error("[Albedo Hub Server Database]: (Unsoloved exception) {}", e.what());
						}
						
					}
				}); // End
			m_thread->detach(); // Daemon Thread
		}
		catch (std::exception& e)
		{
			log::error("[Albedo Hub Server - Database Service]: {}", e.what());
		}

		log::info("[Albedo Hub Server]: Database Service Started!");
	}

}}}} // namespace Albedo::Hub::server::service
#pragma once

#include "../database_service.h"

namespace Albedo{
namespace Hub{
namespace server{
namespace database
{

	class AuthenTable
	{
	public:
		static void insert(std::string_view account, std::string_view password_SHA256)
		{
			/*std::stringstream sql;
			sql << "INSERT INTO authentication(Account, Password) "
				"VALUES('" << account << "', '" << password_SHA256 << "');";

			service::DatabaseService::instance().post(std::make_shared<service::SQL>(sql.str(), false));*/
		}

		static void remove()
		{

		}

		static void update()
		{

		}

		static auto search(std::string_view condition)
		{
			std::stringstream sql;
			sql << "SELECT * FROM authentication WHERE " << condition;
			auto result = std::make_shared<service::SQL>(sql.str(), true);
			service::DatabaseService::instance().post(result);
			return result;
		}
	};

}}}} // namespace Albedo::Hub::server::database
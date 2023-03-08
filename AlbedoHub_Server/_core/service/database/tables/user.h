#pragma once

#include "../database_service.h"

namespace Albedo{
namespace Hub{
namespace server{
namespace database
{

	class UserTable
	{
	public:
		static void insert(std::string_view account, 
									  std::string_view password_SHA256, 
									  std::string_view name)
		{
			std::stringstream sql;
			sql << "INSERT INTO user(Account, Password, Name) "
				"VALUES('" << account << "', '" << password_SHA256 << "', '" << name << "'); ";

			service::DatabaseService::instance().post(std::make_shared<service::SQL>(sql.str(), false));
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
			sql << "SELECT * FROM user WHERE " << condition;
			auto result = std::make_shared<service::SQL>(sql.str(), true);
			service::DatabaseService::instance().post(result);
			return result;
		}

		static auto search_account(std::string_view account)
		{
			std::stringstream sql;
			sql << "SELECT * FROM user WHERE Account = '" << account << "';";
			auto result = std::make_shared<service::SQL>(sql.str(), true);
			service::DatabaseService::instance().post(result);
			return result;
		}
	};

}}}} // namespace Albedo::Hub::server::database
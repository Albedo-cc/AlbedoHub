#pragma once

#include "../database_service.h"

namespace Albedo{
namespace Hub{
namespace Server{
namespace Database
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

			DatabaseService::instance().post(std::make_shared<SQL>(sql.str(), false));
		}

		static void remove()
		{

		}

		static auto update_login_time(std::string_view account)
		{
			std::stringstream sql;
			sql << "UPDATE user SET Time_Login = NOW() WHERE Account = '" << account << "';";
			auto result = std::make_shared<SQL>(sql.str(), false);
			DatabaseService::instance().post(result);
			return result;
		}

		static auto search(std::string_view condition)
		{
			std::stringstream sql;
			sql << "SELECT * FROM user WHERE " << condition;
			auto result = std::make_shared<SQL>(sql.str(), true);
			DatabaseService::instance().post(result);
			return result;
		}

		static auto search_account(std::string_view account)
		{
			std::stringstream sql;
			sql << "SELECT * FROM user WHERE Account = '" << account << "';";
			auto result = std::make_shared<SQL>(sql.str(), true);
			DatabaseService::instance().post(result);
			return result;
		}
	};

}}}} // namespace Albedo::Hub::Server::Database
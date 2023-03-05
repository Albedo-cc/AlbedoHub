#pragma once

#include "../database.h"

namespace Albedo{
namespace Hub{
namespace server
{

	class AuthenTable
	{
	public:
		static void insert(std::string_view account, std::string_view password_SHA256)
		{
			std::stringstream sql;
			sql << "INSERT INTO authentication(Account, Password) "
				"VALUES('" << account << "', '" << password_SHA256 << "');";
			Database::instance().command(sql.str());
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
			return Database::instance().query(sql.str());
		}
	};

}}} // namespace Albedo::Hub::server
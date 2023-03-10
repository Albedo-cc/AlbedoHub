#pragma once

#include "../database_service.h"

namespace Albedo{
namespace Hub{
namespace Server{
namespace Database
{

	class AuthenTable
	{
	public:
		static void insert(std::string_view account, std::string_view password_SHA256)
		{
	
		}

		static void remove()
		{

		}

		static void update()
		{

		}

		static auto search(std::string_view condition)
		{

		}
	};

}}}} // namespace Albedo::Hub::Server::Database
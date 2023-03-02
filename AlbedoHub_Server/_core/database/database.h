#pragma once

#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>
#include <AlbedoDB.hpp>

#include <memory>
#include <string>
#include <unordered_map>
#include <sstream>

namespace Albedo{
namespace Hub{
namespace server
{

	class Database final:
		public pattern::Singleton<Database>,
		public DB::Database
	{
		friend class pattern::Singleton<Database>;

	private:
		Database():
			DB::Database{"127.0.0.1", "root", "@Ljyc741", "albedo-hub-server"}
		{
			log::info("Database Started!");
		};
		virtual ~Database() { log::info("Database Closed!"); }
	};

}}} // namespace Albedo::Hub::server
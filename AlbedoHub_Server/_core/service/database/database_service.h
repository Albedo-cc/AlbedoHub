#pragma once

#include <AlbedoNet.hpp>
#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>
#include <AlbedoDB.hpp>

#include <memory>
#include <mutex>

namespace Albedo{
namespace Hub{
namespace server{
namespace service
{
	class SQL;
	using SQLDeque = net::SafeDeque<std::shared_ptr<SQL>>;

	class DatabaseService final:
		public pattern::Singleton<DatabaseService>
	{
		friend class pattern::Singleton<DatabaseService>;
	public:
		void start();
		void post(std::shared_ptr<SQL> sql)
		{
			m_sql_deque_in->push_back(sql);
		}

		DB::Database& getDatabase() { return m_database; }
	private:
		DatabaseService():
			m_sql_deque{std::make_shared<SQLDeque>()},
			m_sql_deque_in{ std::make_shared<SQLDeque>() }
		{
			
		};
		~DatabaseService() 
		{ 
			log::info("Database Closed!"); 
			size_t lost_SQLs = m_sql_deque->size() + m_sql_deque_in->size();
			if (lost_SQLs) log::critical("You have {} unexecuted SQL(s)!", lost_SQLs);
		}

	private:
		bool hasStarted = false;
		std::unique_ptr<std::thread> m_thread;
		DB::Database m_database{ "127.0.0.1", "root", "@Ljyc741", "albedo-hub-server" };

		std::shared_ptr<SQLDeque> m_sql_deque;
		std::shared_ptr<SQLDeque> m_sql_deque_in;

	private:
		void swap_SQLPool()
		{
			std::scoped_lock guard{ m_sql_deque->get_mutex(), m_sql_deque_in->get_mutex() };
			m_sql_deque.swap(m_sql_deque_in);
		}
	};

	class SQL :
		public pattern::Command
	{
	public:
		SQL() = delete;
		SQL(std::string sql, bool hasResult, bool storeResult = false) :
			m_sql{ std::move(sql) }, isQuery{ hasResult }, bStoreResult{ storeResult } {};
		~SQL() { if (!bExecuted) log::warn("An unexecuted SQL: {}", std::move(m_sql)); }

		virtual void execute() override
		{
			std::scoped_lock guard{ m_mutex };
			if (bExecuted) return; // Canceled or Unexcepted situations

			if (isQuery)
				m_query_result = DatabaseService::instance().getDatabase().query(m_sql, bStoreResult);
			else
				DatabaseService::instance().getDatabase().command(m_sql);

			bExecuted = true;
		}

		bool cancel()
		{
			std::scoped_lock guard{ m_mutex };
			if (bExecuted) return false;
			bExecuted = true;
			return true;
		}

		std::string_view getSQL() const { return m_sql; }

		bool hasExecuted() const { return bExecuted; } // Not lock

		std::shared_ptr<DB::Query> getResult()
		{
			if (!isQuery) log::warn("You are trying to retrive result from a nullptr!");
			return m_query_result;
		}
	protected:
		std::mutex m_mutex;
		bool isQuery = false;
		bool bStoreResult = false;
		bool bExecuted = false;
		std::string m_sql;
		std::shared_ptr<DB::Query> m_query_result;
	};

}}}} // namespace Albedo::Hub::server::service
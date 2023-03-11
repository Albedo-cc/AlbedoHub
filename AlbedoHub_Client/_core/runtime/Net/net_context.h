#pragma once

#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>
#include <AlbedoLog.hpp>

#include <memory>
#include <deque>
#include <optional>
#include <unordered_map>

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{
	struct NetRequest
	{
		NetRequest() = delete;
		NetRequest(net::Message msg) :message{ std::move(msg) } {}
		net::Message message;
		std::string response;
		std::optional<bool> complete;
		bool isExecuted() { return complete.has_value(); }
	};

	class NetContext:
		public pattern::Singleton<NetContext>
	{
		friend class pattern::Singleton<NetContext>;
		friend class Net;
	public:
		bool tryToConnect = false;
		bool isOnline = false;

	public:
		bool sendRequest(std::shared_ptr<NetRequest> request)
		{
			auto& feedback = m_feedbacks[request->message.header.message_id];
			if (feedback == nullptr)
			{
				feedback.swap(request);
				m_requests.emplace_back(feedback);
				return true;
			}
			else return false; // Waiting for being executed
		}

	private:
		NetContext() = default;
		std::deque<std::shared_ptr<NetRequest>> m_requests;
		std::unordered_map<net::MID, std::shared_ptr<NetRequest>> m_feedbacks;
	};

}}}} // namespace Albedo::Hub::Client::Runtime
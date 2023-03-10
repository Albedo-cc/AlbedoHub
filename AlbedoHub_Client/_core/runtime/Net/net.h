#pragma once

#define ALBEDONET_CLIENT
#include <AlbedoNet.hpp>
#include <AlbedoPattern.hpp>

#include <memory>
#include <thread>

namespace Albedo{
namespace Hub{
namespace Client{
namespace Runtime
{
	
	class Net:
		public pattern::Singleton<Net>
	{
	public:
		void update()
		{

		}

	private:
		Net()
			:m_client{std::make_unique<net::Client>()}
		{

		}
	private:
		std::unique_ptr<net::Client> m_client;
	};

}}}} // namespace Albedo::Hub::Client::Runtime
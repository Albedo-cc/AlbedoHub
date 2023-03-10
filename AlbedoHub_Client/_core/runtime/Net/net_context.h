#pragma once

#include <AlbedoPattern.hpp>
#include <memory>

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{

	class NetContext:
		public pattern::Singleton<NetContext>
	{
		friend class pattern::Singleton<NetContext>;
		friend class NetLayer;
	public:
		

	private:
		NetContext() = default;
	};

}}}} // namespace Albedo::Hub::Client::Runtime
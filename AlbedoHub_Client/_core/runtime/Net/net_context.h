#pragma once

#include <AlbedoPattern.hpp>

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

	private:
		NetContext() = default;
	};

}}}} // namespace Albedo::Hub::Client::Runtime
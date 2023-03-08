#pragma once

#include <AlbedoPattern.hpp>

namespace Albedo {
namespace Hub{
namespace client{

	class NetLayerContext:
		public pattern::Singleton<NetLayerContext>
	{
		friend class pattern::Singleton<NetLayerContext>;
		friend class NetLayer;

	private:
		NetLayerContext() = default;
	};

}}} // namespace Albedo::Hub::client
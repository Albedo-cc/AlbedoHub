#pragma once
#include <AlbedoPattern.hpp>

namespace Albedo{
namespace Hub{
namespace Client
{
	class UIContext:
		public pattern::Singleton<UIContext>
	{
		friend class pattern::Singleton<UIContext>;
	public:
		double g_cursor_pos_x = 0.0;
		double g_cursor_pos_y = 0.0;
		int g_window_width = 0;
		int g_window_height = 0;
		bool g_window_is_moving = false;
	private:
		UIContext() = default;
	};

}}} // namespace Albedo::Hub::Client
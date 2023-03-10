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
		// Window
		double g_cursor_pos_x = 0.0;
		double g_cursor_pos_y = 0.0;
		int g_window_width = 0;
		int g_window_height = 0;
		bool g_window_is_moving = false;
		// Menu
		int g_current_menu = 0;
	private:
		UIContext() = default;
	};

	// Images
	enum ImageID
	{
		title_bar_icon,
		default_user_avatar,
	};

}}} // namespace Albedo::Hub::Client
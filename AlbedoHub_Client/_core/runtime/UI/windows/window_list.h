#pragma once
#pragma once

#include "title_bar.h"
#include "menu.h"
#include "content.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{

	enum WindowID
	{
		title_bar_window,
		menu_window,
		content_window,

		max_window_id,
	};

}}}} // namespace Albedo::Hub::Client::Runtime

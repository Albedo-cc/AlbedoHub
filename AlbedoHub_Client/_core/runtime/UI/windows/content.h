#pragma once

#include "window.h"
#include "../backend/image_loader.h"
#include "../../../global_context.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{

	class ContentWindow:
		public Window
	{
	public:
		virtual void render() override
		{
			beginWindow();
			{
				
			}
			endWindow();
		}

	public:
		ContentWindow()
		{
			m_window_name = "Content";
			m_window_size = { 1000 - 160, 600 - 24 };
			m_window_position = { 160, 24 };
			m_window_flags = 
				ImGuiWindowFlags_NoResize | 
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoScrollWithMouse;
		}

	protected:
		virtual void preprocessing() override
		{
		}

		virtual void postprocessing() override
		{
		}
	};
}}}} // namespace Albedo::Hub::Client::Runtime
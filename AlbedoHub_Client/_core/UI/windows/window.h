#pragma once

#include "../backend/imgui_manager.h"

namespace Albedo {
namespace Hub{
namespace client{
namespace layer{
namespace window
{

	class Window
	{
	public:
		virtual void render() = 0;

	protected:
		void beginWindow()
		{
			ImGui::SetNextWindowSize(m_window_size);
			ImGui::SetNextWindowPos(m_window_position);
			ImGui::Begin(m_window_name.c_str(), (bool*)m_is_closable, m_window_flags);
		}

		void endWindow()
		{
			ImGui::End();
		}

	protected:
		std::string m_window_name;
		void* m_is_closable = NULL;

		ImVec2 m_window_size;
		ImVec2 m_window_position;
		ImGuiWindowFlags m_window_flags;
	};

}}}}} // namespace Albedo::Hub::client::layer::window
#pragma once

#include "window.h"
#include "../backend/load_image.h"

namespace Albedo {
namespace Hub{
namespace client{
namespace layer{
namespace window
{
	using namespace ImGui;

	class Home:
		public Window
	{
	public:
		virtual void render() override
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			m_window_position = ImVec2{ viewport->WorkPos };
			m_window_size = ImVec2{ viewport->WorkSize.x, 25.0f };
			//ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2{ 0.0f, 0.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 10.0f, 2.0f });
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.01f, 0.01f, 0.01f, 1.0f });

			beginWindow();
			{
				render_title_bar();
			}
			endWindow();
		}
	private:
		VulkanImage AlbedoHub_icon;

	public:
		Home()
		{
			m_window_name = "Home";
			m_window_flags = 
				ImGuiWindowFlags_NoResize | 
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoScrollWithMouse;
				bool res = ImageLoader::LoadTextureFromFile(
					"C:\\Users\\26692\\Desktop\\×Ï·å¼oÐÐ2023[¡ü]\\GraduationThesis\\Albedo\\logo\\icon.png",
					&AlbedoHub_icon);
				if (!res) log::error("Failed to load image");

		}

	private:

		void render_title_bar()
		{
			ImGui::PopStyleVar(3);
			ImGui::PopStyleColor(1);
			ImGui::Image(static_cast<ImTextureID>(AlbedoHub_icon.DS), //ImVec2(1.0, 1.0));
				ImVec2(AlbedoHub_icon.Width, AlbedoHub_icon.Height));
			ImGui::SetWindowFontScale(1.5f);
			ImGui::SetCursorPos({ 40.0, 2.0 });
;			ImGui::TextColored(ImVec4{ 1.0f,1.0f,1.0f,1.0f }, "Albedo Hub");
		}
	};

}}}}} // namespace Albedo::Hub::client::layer::window
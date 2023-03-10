#pragma once
#pragma once

#include "window.h"
#include "../backend/image_loader.h"
#include "../../../global_context.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{

	class MenuWindow:
		public Window
	{
		enum class Menu
		{
			Home, User
		};
		std::vector<const char*> menus{ "Home", "User" };
	public:
		virtual void render() override
		{
			beginWindow();
			{
				draw_user_info();
				draw_options();
			}
			endWindow();
		}
	private:
		Menu m_current_menu = Menu::Home;
		VulkanImage m_user_avatar;

	public:
		MenuWindow()
		{
			m_window_name = "Menu";
			m_window_size = { 160, 600 - 24 };
			m_window_position = { 0, 24 };
			m_window_flags = 
				ImGuiWindowFlags_NoResize | 
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoScrollWithMouse;

			const char* icon_user = "resource/image/ui_user_avatar_default.png";
			if (!::ImageLoader::LoadTextureFromFile(
				icon_user, &m_user_avatar))
			{
				log::error("Failed to load image ({}) ", icon_user);
				std::exit(-1);
			}
		}

	protected:
		virtual void preprocessing() override
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f });
		}

		virtual void postprocessing() override
		{
			ImGui::PopStyleColor(1);
		}

	private:
		void draw_user_info()
		{
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.0,0.0,0.0, 0.0 });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0,0.0,0.0, 0.0 });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0,0.0,0.0, 0.0 });
			ImGui::SetCursorPos({ 5, 5 });
			ImGui::ImageButton(static_cast<ImTextureID>(m_user_avatar.DS),
				ImVec2(140, 140));
			ImGui::PopStyleColor(3);
			
			ImGui::SetCursorPos({ 5, 150 });
			ImGui::TextColored({ 0,0,0,1 }, "Pet the cat to log in");

			ImGui::GetWindowDrawList()->AddLine({ 5, 178 + 10 }, { 155, 178 + 10 }, ImColor{100, 100, 100, 100}, 2.0f);
		}

		void draw_options()
		{
			float offset_y = 140.0 + 40.0;
			int selected_menu = 0;

			for (const auto& menu : menus)
			{
				ImGui::SetCursorPos({ 10.0f, offset_y });
				if (ImGui::Button(menu, { 140, 50 }))
				{
					m_current_menu = static_cast<Menu>(selected_menu);
				}
				offset_y += 60.0f;
				selected_menu++;
			}	
		}
	};
}}}} // namespace Albedo::Hub::Client::Runtime
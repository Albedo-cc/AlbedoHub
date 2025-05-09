#pragma once
#pragma once

#include "window.h"
#include "../../../global_context.h"
#include "../UI_context.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{
	enum Menu
	{
		// Avatar (Do not add to vector menus!)
		SIGN_IN_OUT,
		// Menu List
		Home,
		User,
		Settings,
	};
	static std::vector<const char*> menus{ "Home", "User", "Settings"};

	class MenuWindow:
		public Window
	{
	public:
		virtual void render() override
		{
			beginWindow();
			{
				draw_user_info();
				draw_options();
				draw_net_state();
			}
			endWindow();
		}
	private:
		VulkanImage& m_user_avatar;

	public:
		MenuWindow():
			m_user_avatar{ ImGUIManager::instance().getImage(ImageID::default_user_avatar)}
		{
			UIContext::instance().g_current_menu = Menu::Home;

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
		}

	protected:
		virtual void preprocessing() override
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f });
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
			if (ImGui::ImageButton(static_cast<ImTextureID>(m_user_avatar.DS), ImVec2(140, 140)))
			{
				UIContext::instance().g_current_menu = Menu::SIGN_IN_OUT;
			}
			ImGui::PopStyleColor(3);
			
			ImGui::SetCursorPos({ 5, 150 });
			ImGui::TextColored({ 0,0,0,1 }, "Pet the cat to log in");

			ImGui::GetWindowDrawList()->AddLine({ 5, 178 + 10 }, { 155, 178 + 10 }, ImColor{100, 100, 100, 100}, 2.0f);
		}

		void draw_options()
		{
			float offset_y = 140.0 + 40.0;
			int selected_menu = static_cast<int>(Menu::Home);

			for (const auto& menu : menus)
			{
				ImGui::SetCursorPos({ 10.0f, offset_y });
				if (ImGui::Button(menu, { 140, 50 }))
				{
					UIContext::instance().g_current_menu = selected_menu;
				}
				offset_y += 60.0f;
				selected_menu++;
			}
		}

		void draw_net_state()
		{
			static time::StopWatch<float> timer;

			auto& netContext = GlobalContext::instance().g_context_Net;
			bool is_online = netContext.isOnline;

			if (is_online) ImGui::BeginDisabled();
			{
				ImGui::SetCursorPosY((600 - 24 - 30));

				static int connect_wait_time = 0; // 5 secs
				static bool should_disable = false;
				static int delta_time = 0;
				if (connect_wait_time)
				{
					delta_time = timer.split().seconds() - connect_wait_time;
					if (delta_time >= 5) connect_wait_time = 0;
				}
				should_disable = is_online || connect_wait_time;
				if (should_disable) ImGui::BeginDisabled();
				if (ImGui::Button("Connect"))
				{
					connect_wait_time = timer.split().seconds();
					netContext.tryToConnect = true;
				}
				if (should_disable) ImGui::EndDisabled();
			}
			if (is_online) ImGui::EndDisabled();
			ImGui::SameLine();
			ImGui::Text("Online : %s", is_online ? "O" : "X");
		}
	};
}}}} // namespace Albedo::Hub::Client::Runtime
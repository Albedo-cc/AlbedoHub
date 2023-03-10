#pragma once

#include "window.h"
#include "../backend/image_loader.h"
#include "../../../global_context.h"
#include "../UI_context.h"

#include "menu.h"

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
			static auto& g_context = UIContext::instance();
			beginWindow();
			{
				switch (g_context.g_current_menu)
				{
				case Menu::Home: draw_home_page(); break;
				case Menu::SIGN_IN_OUT: draw_sign_in_out_page(); break;
				case Menu::User: ImGui::Text("User Page"); break;
				default: log::warn("Selected an undefined Content!");
				}
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

	private:
		void draw_home_page()
		{
			
		}

		void draw_sign_in_out_page()
		{
			static char buffer[(40 + 1) + (64 + 1) + (40 + 1) * 2 + (6 + 1)] = "";
			ImGui::InputTextWithHint("Name", "", buffer, 40, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("EMail", "", buffer + 41, 64, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Password", "", buffer + 106, 40, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Confirm", "Reinput your password", buffer + 147, 40, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			bool is_passwords_equal = true;
			for (int idx = 106;is_passwords_equal && idx < 147; ++idx)
				if ((!buffer[idx] && buffer[idx + 41]) || buffer[idx] != buffer[idx + 41])
					is_passwords_equal = false;
			if (!is_passwords_equal) ImGui::Text("Different Passwords!");
			if (ImGui::Button("Get Verification Code"))
			{
				log::info("Get VCode");
			}
			ImGui::InputTextWithHint("Verfication Code", "", buffer + 188, 6);
			if (ImGui::Button("Register"))
			{
				log::info("Register");
			}
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
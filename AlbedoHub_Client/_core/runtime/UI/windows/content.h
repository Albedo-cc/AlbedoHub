#pragma once

#include "../backend/image_loader.h"
#include "../../../global_context.h"
#include "../UI_context.h"
#include "../../runtime_events.h"

#include "window.h"
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
			auto& netContext = GlobalContext::instance().g_context_Net;
			bool is_online = netContext.isOnline;

			ImGui::Text("Online = %s", is_online ? "Yes" : "No");
			if (is_online) ImGui::BeginDisabled();
			{
				ImGui::SameLine();
				if (ImGui::Button("Connect"))
				{
					netContext.tryToConnect = true;
				}
			}
			if (is_online) ImGui::EndDisabled();

			static int32_t selected_docker = -1;
			if (is_online)
			{
				auto docklist = netContext.getDockList();
				size_t docklist_size = docklist->dockers_size();
				if (!docklist_size) selected_docker = -1;

				if (ImGui::BeginListBox("Online Servers", ImVec2(-FLT_MIN, 30 * ImGui::GetTextLineHeightWithSpacing())))
				{
					for (size_t i = 0; i < docklist_size; ++i)
					{
						bool is_selected = (selected_docker == i);
						auto& curDocker = (docklist->dockers())[i];
						std::string servername = curDocker.name() + " ( " + curDocker.intro() + " )";
						if (ImGui::Selectable(servername.c_str(), is_selected))
							selected_docker = i;

						if (is_selected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndListBox();
				}
			}
		}

		void draw_sign_in_out_page()
		{
			static char buffer[(40 + 1) + (64 + 1) + (40 + 1) * 2 + (6 + 1)] = "";
			ImGui::InputTextWithHint("Name", "", buffer, 41, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("EMail", "", buffer + 41, 65, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Password", "", buffer + 106, 41, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Confirm", "Reinput your password", buffer + 147, 41, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			
			// Check Password
			{
				bool is_passwords_equal = true;
				for (int idx = 106; is_passwords_equal && idx < 147; ++idx)
					if ((!buffer[idx] && buffer[idx + 41]) || buffer[idx] != buffer[idx + 41])
						is_passwords_equal = false;
				if (!is_passwords_equal) ImGui::Text("Different Passwords!");
			}

			ImGui::InputTextWithHint("Verfication Code", "", buffer + 188, 7);

			static bool event_has_sent = false;
			static bool res = false;
			static std::string prompt;

			if (event_has_sent) res = RegisterEvent::isTriggered();
			if (res)
			{
				auto [result, feedback] = RegisterEvent::getResult();
				prompt = (result ? "Successed: " : "Failed: ") + feedback;
				event_has_sent = false;
				res = false;
			}

			if (ImGui::Button("Get Verification Code"))
			{
				RegisterEvent::sendUserInfo(buffer, buffer + 41, buffer + 106);
				event_has_sent = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Register"))
			{
				RegisterEvent::sendVerificationCode(buffer + 188);
				event_has_sent = true;
			}

			ImGui::Text(prompt.c_str());
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
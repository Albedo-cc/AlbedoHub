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
				case Menu::User: draw_user_page(); break;
				case Menu::Settings: draw_settings_page(); break;
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
			auto& globalContext = GlobalContext::instance();
			auto& netContext = globalContext.g_context_Net;
			bool is_online = netContext.isOnline;

			ImGui::SeparatorText("Online Servers");

			static int32_t selected_docker = -1;
			if (!is_online) ImGui::BeginDisabled();
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
						std::string servername = "[ " + std::to_string(i) + " ]\t" +
							curDocker.name() + "\t|\t" +
							curDocker.intro() + "\t|\t" + 
							curDocker.address() + "\t|\t" + 
							std::to_string(curDocker.port());
						if (ImGui::Selectable(servername.c_str(), is_selected))
						{
							selected_docker = i;
							log::info("SELECTED SERVER No.{}", selected_docker);
						}

						if (is_selected)
						{
							ImGui::SetItemDefaultFocus();
							netContext.setSelectedDocker(&curDocker);
						}
					}
					ImGui::EndListBox();
				}
			}
			if (!is_online) ImGui::EndDisabled();

			ImGui::SetCursorPosX(1000 - 160 - 60);
			static std::string cmd;
			if (ImGui::Button("Launch"))
			{
				if (selected_docker >= 0 && netContext.user_profile != nullptr)
				{
					auto selectedDocker = netContext.getSelectedDocker();
					auto& configPath = globalContext.g_Albedo_Config_Path;
					std::ifstream file{ configPath };
					if (file.is_open())
					{
						nlohmann::json config = nlohmann::json::parse(file);
						config["Online"] = "1"; // One-Time configuration
						config["Online_IP"] = selectedDocker->address();
						config["Online_Port"] = std::to_string(selectedDocker->port());
						config["Online_Pass"] = selectedDocker->pass();
						config["Online_UID"] = std::to_string(netContext.user_profile->uid());
						config["Online_Name"] = netContext.user_profile->nickname();
						file.close();

						std::ofstream outfile{ configPath };
						if (outfile.is_open())
						{
							outfile << std::setw(4) << config << std::endl;
							outfile.close();

							std::string cmd = std::format("\"{}\"", globalContext.g_Albedo_Path.c_str());
							globalContext.SystemCall(cmd.c_str());
						}
						else log::error("Failed to save configuration {}", configPath);
					}
					else log::error("Failed to open configuration {}", configPath);
				}
			}
		}

		void draw_sign_in_out_page()
		{
			auto& netContext = GlobalContext::instance().g_context_Net;

			static char buffer_signin[(64 + 1) + (40 + 1)] = "";
			// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			ImGui::SeparatorText("Sign In");
			// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			ImGui::InputTextWithHint("Your EMail", "", buffer_signin, 65, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Your Password", "", buffer_signin + 65, 41, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			
			static bool signio_event_has_sent = false;
			static bool signio_result = false;
			static std::string signio_prompt;

			if (signio_event_has_sent) signio_result = SignIOEvent::isTriggered();
			if (signio_result)
			{
				auto [result, feedback] = SignIOEvent::getResult();
				signio_prompt = (result ? "Successed: " : "Failed: ") + feedback;

				if (result)
				{
					netContext.hasSignedIn = true;
				}

				signio_event_has_sent = false;
				signio_result = false;
			}
			bool ableToSignIO = netContext.isOnline && !netContext.hasSignedIn && !signio_event_has_sent;
			if (!ableToSignIO) ImGui::BeginDisabled();
			if (ImGui::Button("Sign In"))
			{
				SignIOEvent::sendSignInInfo(buffer_signin, buffer_signin + 65);
				signio_event_has_sent = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Sign Out")) { log::warn("Sign Out is invalid now"); }
			if (!ableToSignIO) ImGui::EndDisabled();

			ImGui::Text(signio_prompt.c_str());

			ImGui::Spacing();
			// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			ImGui::SeparatorText("Register");
			// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			static char buffer_register[(40 + 1) + (64 + 1) + (40 + 1) * 2 + (6 + 1)] = "";
			ImGui::InputTextWithHint("Name", "", buffer_register, 41, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("EMail", "", buffer_register + 41, 65, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Password", "", buffer_register + 106, 41, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::InputTextWithHint("Confirm", "Reinput your password", buffer_register + 147, 41, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
			
			// Check Password
			{
				bool is_passwords_equal = true;
				for (int idx = 106; is_passwords_equal && idx < 147; ++idx)
					if ((!buffer_register[idx] && buffer_register[idx + 41]) || buffer_register[idx] != buffer_register[idx + 41])
						is_passwords_equal = false;
				if (!is_passwords_equal) ImGui::Text("Different Passwords!");
			}

			ImGui::InputTextWithHint("Verfication Code", "", buffer_register + 188, 7);

			static bool register_event_has_sent = false;
			static bool register_result = false;
			static std::string register_prompt;

			if (register_event_has_sent) register_result = RegisterEvent::isTriggered();
			if (register_result)
			{
				auto [result, feedback] = RegisterEvent::getResult();
				register_prompt = (result ? "Successed: " : "Failed: ") + feedback;
				register_event_has_sent = false;
				register_result = false;
			}

			if (ImGui::Button("Get Verification Code"))
			{
				RegisterEvent::sendUserInfo(buffer_register, buffer_register + 41, buffer_register + 106);
				register_event_has_sent = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Register"))
			{
				RegisterEvent::sendVerificationCode(buffer_register + 188);
				register_event_has_sent = true;
			}

			ImGui::Text(register_prompt.c_str());
		}

		void draw_settings_page()
		{
			auto& gContext = GlobalContext::instance();

			ImGui::SeparatorText("Application");
			ImGui::InputTextWithHint("Albedo APP Path", "",
				gContext.g_Albedo_Path.data(),
				gContext.g_Albedo_Path.size());
			ImGui::InputTextWithHint("Albedo Config Path", "",
				gContext.g_Albedo_Config_Path.data(),
				gContext.g_Albedo_Config_Path.size());
		}

		void draw_user_page()
		{
			auto& netContext = GlobalContext::instance().g_context_Net;

			ImGui::SeparatorText("Basic Info");

			if (netContext.user_profile == nullptr)
			{
				char placeholder{};
				ImGui::InputTextWithHint("UID", "Please click the avatar and sign in first", &placeholder, 1, ImGuiInputTextFlags_ReadOnly);
				ImGui::InputTextWithHint("Name", "Please click the avatar and sign in first", &placeholder, 1, ImGuiInputTextFlags_ReadOnly);
			}
			else
			{
				static std::string uid = std::to_string(netContext.user_profile->uid());
				ImGui::InputText("UID", uid.data(), uid.size(), ImGuiInputTextFlags_ReadOnly);
				static char* name = (char*)netContext.user_profile->nickname().c_str();
				ImGui::InputText("Name", name, netContext.user_profile->nickname().size(), ImGuiInputTextFlags_ReadOnly);
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
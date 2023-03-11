#pragma once

#include "../backend/image_loader.h"
#include "../../../global_context.h"
#include "../UI_context.h"

#include "window.h"
#include "menu.h"

#include <AlbedoProtocol.pb.h>
#include <register_protocol.pb.h>

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
			ImGui::Text("Online = %d", GlobalContext::instance().g_context_Net.isOnline);
			if (!GlobalContext::instance().g_context_Net.isOnline && ImGui::Button("Connect"))
			{
				GlobalContext::instance().g_context_Net.tryToConnect = true;
			}
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

			static std::shared_ptr<NetRequest> net_req;
			auto& net = GlobalContext::instance().g_context_Net;
			if (ImGui::Button("Get Verification Code"))
			{
				log::info("Get VCode");

				RegisterProtocol::UserInfo userinfo{ };
				userinfo.set_name(std::string(buffer));
				userinfo.set_account(std::string(buffer + 41));
				userinfo.set_password(std::string(buffer + 106));
				
				if (net_req == nullptr)
				{
					net_req = std::make_shared<NetRequest>
					(
						net::Message
						{
							AlbedoProtocol::PID::REGISTER_CLIENT_SEND_REQUEST,
							userinfo.SerializeAsString()
						}
					);
					net.sendRequest(net_req);
				}
				
			}
			ImGui::InputTextWithHint("Verfication Code", "", buffer + 188, 6);
			
			if (net.isOnline && ImGui::Button("Register"))
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
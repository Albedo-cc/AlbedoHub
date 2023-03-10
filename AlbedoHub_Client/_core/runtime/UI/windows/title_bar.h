#pragma once

#include "window.h"
#include "../backend/image_loader.h"
#include "../../../global_context.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{

	class TitleBarWindow:
		public Window
	{
	public:
		virtual void render() override
		{
			beginWindow();
			{
				ImGui::SetCursorPos({ 16, 2.0 });
				ImGui::Image(static_cast<ImTextureID>(AlbedoHub_icon.DS),
					ImVec2(AlbedoHub_icon.Width, AlbedoHub_icon.Height));
				ImGui::SetCursorPos({ 1000 - 22, 2.0 });
				if (ImGui::Button("X", { 20,20 }))
				{
					GlobalContext::instance().shutdown("[Home Window Close Button]");
				}
			}
			endWindow();
		}
	private:
		VulkanImage AlbedoHub_icon;

	public:
		TitleBarWindow()
		{
			m_window_name = "Title Bar";
			m_window_flags = 
				ImGuiWindowFlags_NoResize | 
				ImGuiWindowFlags_NoTitleBar |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoMove |
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_NoSavedSettings |
				ImGuiWindowFlags_NoScrollWithMouse;

			// Load Title Bar Icon
			const char* icon_title_bar = "resource/image/ui_title_bar.png";
			if (!::ImageLoader::LoadTextureFromFile(
				icon_title_bar, &AlbedoHub_icon))
			{
				log::error("Failed to load image ({}) ", icon_title_bar);
				std::exit(-1);
			}
		}

		~TitleBarWindow()
		{
			::ImageLoader::RemoveTexture(&AlbedoHub_icon);
		}

	protected:
		virtual void preprocessing() override
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			m_window_position =  viewport->WorkPos;
			m_window_size = std::move(ImVec2{ viewport->WorkSize.x, 24.0f });

			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2{ 0.0f, 0.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 2.0f });
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f });
		}

		virtual void postprocessing() override
		{
			ImGui::PopStyleVar(3);
			ImGui::PopStyleColor(1);
		}
	};

}}}} // namespace Albedo::Hub::Client::Runtime
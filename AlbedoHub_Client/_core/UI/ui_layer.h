#pragma once

#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>

#include "include/imgui_manager.h"
#include "../albedo_hub_context.h"

namespace Albedo {
namespace Hub{
namespace client{
namespace layer
{
    class UI :
        public pattern::Singleton<UI>
    {
        friend class pattern::Singleton<UI>;
    public:
        void update()
        {
            if (!AlbedoHubContext::instance().isRunning()) return;
            auto& MImGUI = ImGUIManager::instance();
            if (MImGUI.shoudClose())
            {
                AlbedoHubContext::instance().shutdown("UI Layer - glfwWindowShouldClose()");
                return;
            }

            MImGUI.beginFrame();

            static bool testbool = false;
            static int testint = 10;

            ImGui::SetNextWindowSize(ImVec2(400, 400));
            auto WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
            if (ImGui::Begin("Main", NULL, WindowFlags))
            {
                ImGui::Checkbox("Test Bool", &testbool);
                if (ImGui::Button("Confirm"))
                {
                    log::info("Confirm Button");
                }

                ImGui::SliderInt("##d", &testint, 0, 100);

                ImGui::SetCursorPos(ImVec2(200, 100));
                if (ImGui::Button("Test", ImVec2(30, 30)))
                {

                }
            }ImGui::End();

            MImGUI.endFrame();
        }
    private:
        UI() { ImGUIManager::instance(); } // Pre-init
    };

}}}} // namespace Albedo::Hub::client::layer
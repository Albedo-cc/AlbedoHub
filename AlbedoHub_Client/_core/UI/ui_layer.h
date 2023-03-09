#pragma once

#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>

#include "windows/window.h"
#include "windows/window_list.h"
#include "../albedo_hub_context.h"

namespace Albedo {
namespace Hub{
namespace client{
namespace layer
{
    using namespace window;

    class UI :
        public pattern::Singleton<UI>
    {
        friend class pattern::Singleton<UI>;
    public:
        void update()
        {
            if (MImGUI.shoudClose())
                AlbedoHubContext::instance().shutdown("UI Layer - glfwWindowShouldClose()");
            if (!AlbedoHubContext::instance().isRunning()) return;

            handle_window_move();

            MImGUI.beginFrame();
            {
                for (const auto& window : m_window_list)
                {
                    if (window) window->render();
                }
            }
            MImGUI.endFrame();
        }
    private:
        std::vector<std::unique_ptr<Window>> m_window_list;
        ImGUIManager& MImGUI = ImGUIManager::instance();

        // The following members will be moved to UIContext
        double g_cursor_pos_x;
        double g_cursor_pos_y;
        int g_window_width;
        int g_window_height;
        bool g_window_is_moving = false;
    private:
        UI() :
            m_window_list(WindowID::max_window_id)
        { 
            m_window_list[WindowID::home_window] = std::make_unique<window::Home>();
            //m_window_list[WindowID::register_window] = std::make_unique<window::Register>();
        } 

        void handle_window_move()
        {
            auto* window = MImGUI.window;
            if (glfwGetMouseButton(window, 0) == GLFW_PRESS && !g_window_is_moving)
            {
                glfwGetCursorPos(window, &g_cursor_pos_x, &g_cursor_pos_y);
                glfwGetWindowSize(window, &g_window_width, &g_window_height);
                g_window_is_moving = true;
            }
            if (glfwGetMouseButton(window, 0) == GLFW_PRESS && g_window_is_moving)
            {
                double c_xpos, c_ypos;
                int w_xpos, w_ypos;
                glfwGetCursorPos(window, &c_xpos, &c_ypos);
                glfwGetWindowPos(window, &w_xpos, &w_ypos);
                if (
                    g_cursor_pos_x >= 0 && g_cursor_pos_x <= ((double)(g_window_width - 170))
                    &&
                    g_cursor_pos_y >= 0 && g_cursor_pos_y <= 25) {
                    glfwSetWindowPos(window, w_xpos + (c_xpos - g_cursor_pos_x), w_ypos + (c_ypos - g_cursor_pos_y));
                }
                if (
                    g_cursor_pos_x >= (double)(g_window_width - 15)
                    && g_cursor_pos_x <= (double)(g_window_width) &&
                    g_cursor_pos_y >= (double)(g_window_height - 15)
                    && g_cursor_pos_y <= (double)(g_window_height)) {
                    glfwSetWindowSize(window,
                        g_window_width + (c_xpos - g_cursor_pos_x),
                        g_window_height + (c_ypos - g_cursor_pos_y));
                }
            }
            if (glfwGetMouseButton(window, 0) == GLFW_RELEASE && g_window_is_moving)
            {
                g_window_is_moving = false;
            }
        }
    };

}}}} // namespace Albedo::Hub::client::layer
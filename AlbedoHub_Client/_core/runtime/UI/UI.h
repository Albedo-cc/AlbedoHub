#pragma once

#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>

#include "windows/window.h"
#include "windows/window_list.h"
#include "../../global_context.h"
#include "UI_context.h"

namespace Albedo {
namespace Hub{
namespace Client{
namespace Runtime
{

    class UI :
        public pattern::Singleton<UI>
    {
        friend class pattern::Singleton<UI>;
    public:
        void update()
        {

            if (MImGUI.shoudClose())
                GlobalContext::instance().shutdown("UI Layer - glfwWindowShouldClose()");
            if (!GlobalContext::instance().isRunning()) return;

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

    private:
        UI() :
            m_window_list(WindowID::max_window_id)
        {
            MImGUI.loadImage(ImageID::title_bar_icon, "resource/image/ui_title_bar.png");
            MImGUI.loadImage(ImageID::default_user_avatar, "resource/image/ui_user_avatar_default.png");

            m_window_list[WindowID::title_bar_window] = std::make_unique<TitleBarWindow>();
            m_window_list[WindowID::menu_window] = std::make_unique<MenuWindow>();
            m_window_list[WindowID::content_window] = std::make_unique<ContentWindow>();
        } 

        void handle_window_move()
        {
            auto& context = UIContext::instance();
            auto* window = MImGUI.window;
            if (glfwGetMouseButton(window, 0) == GLFW_PRESS && !context.g_window_is_moving)
            {
                glfwGetCursorPos(window, &context.g_cursor_pos_x, &context.g_cursor_pos_y);
                glfwGetWindowSize(window, &context.g_window_width, &context.g_window_height);
                context.g_window_is_moving = true;
            }
            if (glfwGetMouseButton(window, 0) == GLFW_PRESS && context.g_window_is_moving)
            {
                double c_xpos, c_ypos;
                int w_xpos, w_ypos;
                glfwGetCursorPos(window, &c_xpos, &c_ypos);
                glfwGetWindowPos(window, &w_xpos, &w_ypos);
                if (
                    context.g_cursor_pos_x >= 0 && context.g_cursor_pos_x <= ((double)(context.g_window_width))
                    &&
                    context.g_cursor_pos_y >= 0 && context.g_cursor_pos_y <= 25) {
                    glfwSetWindowPos(window, w_xpos + (c_xpos - context.g_cursor_pos_x), w_ypos + (c_ypos - context.g_cursor_pos_y));
                }
                if (
                    context.g_cursor_pos_x >= (double)(context.g_window_width - 15)
                    && context.g_cursor_pos_x <= (double)(context.g_window_width) &&
                    context.g_cursor_pos_y >= (double)(context.g_window_height - 15)
                    && context.g_cursor_pos_y <= (double)(context.g_window_height)) {
                    glfwSetWindowSize(window,
                        context.g_window_width + (c_xpos - context.g_cursor_pos_x),
                        context.g_window_height + (c_ypos - context.g_cursor_pos_y));
                }
            }
            if (glfwGetMouseButton(window, 0) == GLFW_RELEASE && context.g_window_is_moving)
            {
                context.g_window_is_moving = false;
            }
        }
    };

}}}} // namespace Albedo::Hub::Client::Runtime
#pragma once
#pragma once

#include "home.h"
#include "register.h"

namespace Albedo {
namespace Hub{
namespace client{
namespace layer{
namespace window
{

	enum WindowID
	{
		home_window,
		register_window,

		max_window_id,
	};

}}}}} // namespace Albedo::Hub::client::layer::window
//
//static bool testbool = false;
//static int testint = 10;
//
//ImGui::SetNextWindowSize(ImVec2(400, 400));
//auto WindowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
//if (ImGui::Begin("Main", NULL, WindowFlags))
//{
//    ImGui::Checkbox("Test Bool", &testbool);
//    if (ImGui::Button("Confirm"))
//    {
//        log::info("Confirm Button");
//    }
//
//    ImGui::SliderInt("##d", &testint, 0, 100);
//
//    ImGui::SetCursorPos(ImVec2(200, 100));
//    if (ImGui::Button("Test", ImVec2(30, 30)))
//    {
//
//    }
//}ImGui::End();
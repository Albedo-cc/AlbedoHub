#pragma once

#include <AlbedoLog.hpp>
#include <AlbedoPattern.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>
#include <cstdlib>
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

namespace Albedo {
namespace Hub{
namespace client{
namespace layer
{
	
	class ImGUIManager:
		public pattern::Singleton<ImGUIManager>
	{
		friend class pattern::Singleton<ImGUIManager>;
	public:
        bool shoudClose() const { return glfwWindowShouldClose(window); }

        void beginFrame();
        void endFrame();

	private:
		ImGUIManager();
		~ImGUIManager();

    // Backend Functions
    private:
        int initVulkan();
        void SetupVulkan(const char** extensions, uint32_t extensions_count);
        void SetupVulkanWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height);
        void CleanupVulkan();
        void CleanupVulkanWindow();
        void FrameRender(ImGui_ImplVulkanH_Window* wd, ImDrawData* draw_data);
        void FramePresent(ImGui_ImplVulkanH_Window* wd);

	private:
        bool show_demo_window = true;
        bool show_another_window = true;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        GLFWwindow* window = NULL;
        VkAllocationCallbacks* g_Allocator = NULL;
        VkInstance g_Instance = VK_NULL_HANDLE;
        VkPhysicalDevice g_PhysicalDevice = VK_NULL_HANDLE;
        VkDevice g_Device = VK_NULL_HANDLE;
        uint32_t g_QueueFamily = (uint32_t)-1;
        VkQueue g_Queue = VK_NULL_HANDLE;
        VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
        VkPipelineCache g_PipelineCache = VK_NULL_HANDLE;
        VkDescriptorPool g_DescriptorPool = VK_NULL_HANDLE;

        ImGui_ImplVulkanH_Window g_MainWindowData;
        ImGui_ImplVulkanH_Window* wd = nullptr;
        int g_MinImageCount = 2;
        bool g_SwapChainRebuild = false;
	};

}}}} // namespace Albedo::Hub::client::layer
add_library(AlbedoHub_Client_Libs INTERFACE)

# Vulkan
if (NOT TARGET vulkan)
    message(STATUS "\nLoading Vulkan (vulkan)")
    add_subdirectory(vulkanSDK)
    
    target_link_libraries(AlbedoHub_Client_Libs INTERFACE vulkan)
endif()

# GLFW
if(NOT TARGET glfw)
    message(STATUS "\nLoading GLFW (glfw)")
    option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
    option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
    option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
    option(GLFW_INSTALL "Generate installation target" OFF)
    option(GLFW_VULKAN_STATIC "Assume the Vulkan loader is linked with the application" OFF)
    add_subdirectory(glfw-3.3.8)

    
    target_link_libraries(AlbedoHub_Client_Libs INTERFACE glfw)
endif()

# Dear ImGui
if (NOT TARGET imgui)
    message(STATUS "\nLoading Dear ImGui (imgui)")
    add_subdirectory(imgui-1.89.2)
    target_link_libraries(imgui PUBLIC vulkan)
    target_link_libraries(imgui PUBLIC glfw)

    target_link_libraries(AlbedoHub_Client_Libs INTERFACE imgui)
endif()
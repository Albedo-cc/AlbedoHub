cmake_minimum_required(VERSION 3.21.0 FATAL_ERROR)

project("AlbedoHub"
    LANGUAGES CXX
    VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Explicitly require the standard
set(CMAKE_CXX_EXTENSIONS OFF) # Vendor-specific Extensions

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/_script")

add_subdirectory(_common)


add_subdirectory(AlbedoHub_Client)
add_subdirectory(AlbedoHub_Server)
makeProtobufTarget(Protocol "${PROJECT_SOURCE_DIR}/_protocol" "${PROJECT_SOURCE_DIR}/_protocol/include")
target_link_libraries(AlbedoHub_Client PRIVATE Protocol)
target_link_libraries(AlbedoHub_Server PRIVATE Protocol)

include(target_put_into_folder)
# Common
target_put_into_folder(AlbedoLog "AlbedoHub/Extern/Common/AlbedoLog")
    target_put_into_folder(spdlog "AlbedoHub/Extern/Common/AlbedoLog/3rdParty/spdlog")
target_put_into_folder(AlbedoPattern "AlbedoHub/Extern/Common/AlbedoPattern")
target_put_into_folder(AlbedoNet "AlbedoHub/Extern/Common/AlbedoNet")
    target_put_into_folder(asio "AlbedoHub/Extern/Common/AlbedoNet/3rdParty/ASIO")
    target_put_into_folder(cryptopp "AlbedoHub/Extern/Common/AlbedoNet/3rdParty/Crypto++")
target_put_into_folder(JSON "AlbedoHub/Extern/Common/JSON")
target_put_into_folder(stb_image "AlbedoHub/Extern/Common/stb_image")
target_put_into_folder(protobuf "AlbedoHub/Extern/Common/Protocol_Buffer")


# Server
target_put_into_folder(AlbedoHub_Server "AlbedoHub/Server")
    target_put_into_folder(AlbedoDB "AlbedoHub/Extern/Server/AlbedoDB")
# Client
target_put_into_folder(AlbedoHub_Client "AlbedoHub/Client")
    target_put_into_folder(imgui "AlbedoHub/Extern/Client/Dear_ImGUI")
    target_put_into_folder(vulkan "AlbedoHub/Extern/Client/Vulkan")
    target_put_into_folder(glfw "AlbedoHub/Extern/Client/GLFW")
    target_put_into_folder(update_mappings "AlbedoHub/Extern/Client/GLFW")

#Protocol
target_put_into_folder(Protocol "AlbedoHub/Protocol")

project("AlbedoHub_Client" 
    LANGUAGES CXX
    VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Explicitly require the standard
set(CMAKE_CXX_EXTENSIONS OFF) # Vendor-specific Extensions

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/_script")
set(EXTERNAL_DEPENDENCY_FOLADER "AlbedoHub/Client/3rdParty")

add_subdirectory(_extern)
add_subdirectory(_core)

add_subdirectory(AlbedoHub_Client)
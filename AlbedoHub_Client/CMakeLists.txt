project("AlbedoHub_Client" 
    LANGUAGES CXX
    VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Explicitly require the standard
set(CMAKE_CXX_EXTENSIONS OFF) # Vendor-specific Extensions

add_subdirectory(_extern)
add_subdirectory(_core)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
    AlbedoHub_Common_Libs
    AlbedoHub_Client_Libs)
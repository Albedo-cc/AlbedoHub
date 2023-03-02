add_library(AlbedoHub_Server_Libs INTERFACE)

# AlbedoDB
if (NOT TARGET AlbedoDB)
    message(STATUS "\nLoading AlbedoDB (Albedo::DB)")
    set(ALBEDO_LIBS_SHARED_TARGET ${PROJECT_NAME})
    add_subdirectory(AlbedoDB)
    target_link_libraries(AlbedoHub_Server_Libs INTERFACE Albedo::DB)
endif()
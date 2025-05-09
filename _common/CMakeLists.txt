# Albedo Log
if (NOT TARGET Albedo::log)
    message(STATUS "\nLoading Albedo Log (Albedo::log)")
    add_subdirectory(AlbedoLog)
endif()

# Albedo Utils
if (NOT TARGET Albedo::utils)
    message(STATUS "\nLoading Albedo Utils (Albedo::utils)")
    add_subdirectory(AlbedoUtils)
endif()

# Albedo Net
if (NOT TARGET Albedo::net)
    message(STATUS "\nLoading Albedo Log (Albedo::net)")
    add_subdirectory(AlbedoNet)
endif()

# JSON
if (NOT TARGET JSON)
    message(STATUS "\nLoading nlohmann-json (JSON)")
    add_subdirectory(JSON-nlohmann)
endif()

# Protocol Buffers
if (NOT TARGET protobuf)
    message(STATUS "\nLoading Protocol Buffers (protobuf)")
    # option(protobuf_BUILD_TESTS "" OFF)
    # option(protobuf_MSVC_STATIC_RUNTIME "" ON)
    # option(protobuf_BUILD_EXAMPLES "" OFF)
    # option(protobuf_BUILD_PROTOC_BINARIES "" OFF)
    add_subdirectory(protobuf-3.21.12)
endif()

add_library(AlbedoHub_Common_Libs INTERFACE)
target_link_libraries(AlbedoHub_Common_Libs
    INTERFACE
    Albedo::log
    Albedo::utils
    Albedo::net
    JSON
    protobuf)
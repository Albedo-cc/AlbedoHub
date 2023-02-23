# Albedo Log
if (NOT TARGET Albedo::log)
    message(STATUS "\nLoading Albedo Log (Albedo::log)")
    add_subdirectory(AlbedoLog)
endif()

# Albedo Net
if (NOT TARGET Albedo::log)
    message(STATUS "\nLoading Albedo Log (Albedo::net)")
    add_subdirectory(AlbedoNet)
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
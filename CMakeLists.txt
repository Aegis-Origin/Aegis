cmake_minimum_required(VERSION 3.20)

project(Aegis LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "Aegis currently only supports Windows.")
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

# Keep the engine DLL next to the executable for each build configuration.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>")

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Aegis/vendor/spdlog/CMakeLists.txt")
    message(FATAL_ERROR "spdlog is missing. Run: git submodule update --init --recursive")
endif()
add_subdirectory(Aegis/vendor/spdlog EXCLUDE_FROM_ALL)

add_library(Aegis SHARED
    Aegis/src/Aegis.h
    Aegis/src/Aegis/Application.cpp
    Aegis/src/Aegis/Application.h
    Aegis/src/Aegis/Core.h
    Aegis/src/Aegis/EntryPoint.h
    Aegis/src/Aegis/Log.cpp
    Aegis/src/Aegis/Log.h
)
target_compile_features(Aegis PUBLIC cxx_std_20)
target_include_directories(Aegis PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Aegis/src")
target_compile_definitions(Aegis
    PUBLIC AG_PLATFORM_WINDOWS
    PRIVATE AG_BUILD_DLL
)
# Log.h exposes spdlog types, so consumers need its headers as well.
target_link_libraries(Aegis PUBLIC spdlog::spdlog_header_only)

add_executable(Sandbox Sandbox/src/SandboxApp.cpp)
target_link_libraries(Sandbox PRIVATE Aegis)

if(MSVC)
    target_compile_options(Aegis PRIVATE /W3 /permissive- /utf-8)
    target_compile_options(Sandbox PRIVATE /W3 /permissive- /utf-8)
endif()

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Sandbox)

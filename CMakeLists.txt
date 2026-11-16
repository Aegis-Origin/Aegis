cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

# -----------------------------------------------------------------------------
# Project
# -----------------------------------------------------------------------------
project(
    Aegis
    VERSION 0.1.0
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# -----------------------------------------------------------------------------
# Includes
# -----------------------------------------------------------------------------
include(AegisFunctions)
include(AegisDependencies)
include(GenerateExportHeader)

find_package(Git QUIET)

# -----------------------------------------------------------------------------
# Options
# -----------------------------------------------------------------------------
option(AG_BUILD_STRICT "Build with warnings as errors" ON)
option(AG_ENABLE_ASAN "Build with address sanitization" OFF)
option(AG_ENABLE_UBSAN "Build with undefined behavior sanitization" OFF)
option(AG_ENABLE_TSAN "Build with thread sanitization" OFF)

# -----------------------------------------------------------------------------
# Standard
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# Output Directories
# -----------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# -----------------------------------------------------------------------------
# Platform Detection
# -----------------------------------------------------------------------------
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(STATUS "Building Aegis for Windows")
    set(AG_PLATFORM_WINDOWS ON)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Building Aegis for Linux")
    set(AG_PLATFORM_LINUX ON)
else()
    message(FATAL_ERROR "Aegis is not supported on ${CMAKE_SYSTEM_NAME}")
endif()

# -----------------------------------------------------------------------------
# Subdirectories
# -----------------------------------------------------------------------------
add_subdirectory(Aegis)
add_subdirectory(Sandbox)

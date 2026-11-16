# ------------------------------------------------------------------------------
# Library
# ------------------------------------------------------------------------------
add_library(Aegis)
add_library(Aegis::Aegis ALIAS Aegis)

# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------
set_target_properties(
    Aegis PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        COMPILE_WARNING_AS_ERROR ${AG_BUILD_STRICT}
        POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
)

target_compile_features(Aegis PUBLIC cxx_std_23)

aegis_apply_warnings(Aegis)
aegis_apply_sanitization(
    Aegis
    ASAN ${AG_ENABLE_ASAN}
    UBSAN ${AG_ENABLE_UBSAN}
    TSAN ${AG_ENABLE_TSAN}
)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------
target_sources(
    Aegis
    PRIVATE
        "Source/Core/Log.cpp"
)

# -----------------------------------------------------------------------------
# Includes
# -----------------------------------------------------------------------------
target_include_directories(
    Aegis
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        "${CMAKE_CURRENT_BINARY_DIR}/Generated"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
target_link_libraries(Aegis
    PUBLIC
        spdlog::spdlog_header_only
)

if(MSVC)
    # Required by spdlog's fmt library
    target_compile_options(Aegis PUBLIC /utf-8)
endif()

# -----------------------------------------------------------------------------
# Generated Headers
# -----------------------------------------------------------------------------
set(AG_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/Generated")
set(AG_GIT_COMMIT_HASH "unknown")

generate_export_header(
    Aegis
    BASE_NAME AG
    EXPORT_FILE_NAME "${AG_GENERATED_DIR}/Aegis/Export.hpp"
)

if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(Aegis PUBLIC AG_STATIC_DEFINE)
endif()

if(GIT_FOUND)
    execute_process(
        COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        OUTPUT_VARIABLE _git_hash
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE _git_result
        ERROR_QUIET
    )
    if(_git_result EQUAL 0 AND NOT _git_hash STREQUAL "")
        set(AG_GIT_COMMIT_HASH "${_git_hash}")
    endif()
endif()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Include/Aegis/Version.hpp.in"
    "${AG_GENERATED_DIR}/Aegis/Version.hpp" @ONLY
)

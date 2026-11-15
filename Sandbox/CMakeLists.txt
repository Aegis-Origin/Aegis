# ------------------------------------------------------------------------------
# Executable
# ------------------------------------------------------------------------------
add_executable(Sandbox)

# ------------------------------------------------------------------------------
# Configuration
# ------------------------------------------------------------------------------
set_target_properties(
    Sandbox PROPERTIES
        COMPILE_WARNING_AS_ERROR ${AG_BUILD_STRICT}
)

target_link_libraries(Sandbox PRIVATE Aegis::Aegis)
target_compile_features(Sandbox PUBLIC cxx_std_23)

aegis_apply_warnings(Sandbox)
aegis_apply_sanitization(
    Sandbox
    ASAN ${AG_ENABLE_ASAN}
    UBSAN ${AG_ENABLE_UBSAN}
    TSAN ${AG_ENABLE_TSAN}
)

# -----------------------------------------------------------------------------
# Sources
# -----------------------------------------------------------------------------
target_sources(
    Sandbox
    PRIVATE
        "Source/Main.cpp"
)

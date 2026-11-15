function(aegis_apply_warnings target)
    if(NOT TARGET ${target})
        message(FATAL_ERROR "${target} is not a target")
    endif()

    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()


function(aegis_apply_sanitization target)
    cmake_parse_arguments(PARSE_ARGV 1 arg "" "ASAN;UBSAN;TSAN" "")

    if(NOT arg_ASAN AND NOT arg_UBSAN AND NOT arg_TSAN)
        return()
    endif()

    if(arg_ASAN AND arg_TSAN)
        message(FATAL_ERROR "ASAN and TSAN are mutually exclusive")
    endif()

    if(MSVC)
        if(arg_UBSAN OR arg_TSAN)
            message(WARNING "Only ASAN is supported with MSVC-style compilers")
        endif()
        if(arg_ASAN)
            target_compile_options(${target} PRIVATE /fsanitize=address)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(
            sanitizers
                $<$<BOOL:${arg_ASAN}>:address>
                $<$<BOOL:${arg_UBSAN}>:undefined>
                $<$<BOOL:${arg_TSAN}>:thread>
        )

        set(flag "-fsanitize=$<JOIN:${sanitizers},$<COMMA>>")

        target_link_options(${target} PRIVATE ${flag})
        target_compile_options(
            ${target}
            PRIVATE
                ${flag}
                -fno-omit-frame-pointer
        )
    else()
        message(WARNING "Sanitizers not supported for ${CMAKE_CXX_COMPILER_ID}")
    endif()
endfunction()

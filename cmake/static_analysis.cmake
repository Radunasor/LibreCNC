set(STATIC_ANALYSIS_ENABLED ${PROJECT_NAME}_STATIC_ANALYSIS)
string(TOUPPER ${STATIC_ANALYSIS_ENABLED} STATIC_ANALYSIS_ENABLED_UPPER)

option(${STATIC_ANALYSIS_ENABLED_UPPER} "Enable static analysis for ${PROJECT_NAME} project." OFF)

if(${STATIC_ANALYSIS_ENABLED_UPPER})
    find_program(CLANG_TIDY_COMMAND NAMES "clang-tidy")

    if(NOT CLANG_TIDY_COMMAND)
        message(WARNING "CMake_RUN_CLANG_TIDY for static analysis is ON but clang-tidy binary is not found!")
        set(CMAKE_C_CLANG_TIDY "" CACHE STRING "" FORCE)
    else()
        message(STATUS "CMake_RUN_CLANG_TIDY for static analysis is ON")

        set(CLANG_TIDY_COMMAND "${CLANG_TIDY_COMMAND}")

        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    endif()
endif()
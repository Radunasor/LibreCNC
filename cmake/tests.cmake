set(BUILD_ENABLED ${PROJECT_NAME}_BUILD_TESTS)
string(TOUPPER ${BUILD_ENABLED} BUILD_ENABLED)

option(${BUILD_ENABLED} "build tests for the \"${PROJECT_NAME}\" project." OFF)

if(${${BUILD_ENABLED}})
    get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)

    set(INSTALL_GTEST OFF CACHE BOOL "don't install gtest by default.")

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG origin/main
    )
    FetchContent_MakeAvailable(googletest)

    include(CTest)
    include(GoogleTest)

    set(TEST_ENTRY_TARGET_NAME ${PROJECT_NAME}_test)
    add_library(${TEST_ENTRY_TARGET_NAME} OBJECT tests/main.cpp)
    target_link_libraries(${TEST_ENTRY_TARGET_NAME} PRIVATE gtest)

    file(GLOB PROJECT_TESTS LIST_DIRECTORIES false tests/*.cpp)
    list(REMOVE_ITEM PROJECT_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp)

    foreach(SOURCE ${PROJECT_TESTS})
        cmake_path(GET SOURCE STEM TEST_FILE_NAME)
        set(TEST_TARGET_NAME test_${TEST_FILE_NAME})
        add_executable(${TEST_TARGET_NAME} ${SOURCE} $<TARGET_OBJECTS:${TEST_ENTRY_TARGET_NAME}>)
        target_link_libraries(${TEST_TARGET_NAME} PRIVATE ${PROJECT_NAME} gtest gmock)
        gtest_discover_tests(${TEST_TARGET_NAME})
    endforeach()

    get_cmake_property(ALL_VARIABLES VARIABLES)

    foreach(VARIABLE ${ALL_VARIABLES})
        string(REGEX MATCH "_TESTS$" IS_TEST_LIST ${VARIABLE})

        if(IS_TEST_LIST)
            foreach(TEST ${${VARIABLE}})
                message(STATUS "Running ${TEST}")
            endforeach()
        endif()
    endforeach()
endif()
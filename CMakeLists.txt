cmake_minimum_required(VERSION 3.21.1)

project(librecnc LANGUAGES C CXX VERSION 4.5.6)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_STANDARD 11)

configure_file(include/${PROJECT_NAME}_config.h.in ${PROJECT_NAME}_config.h)

# include(FetchContent)

# option(BUILD_SHARED_LIBS "override the BUILD_SHARED_LIBS in LVGL cmake files" ON)
# FetchContent_Declare(
# lvgl
# GIT_REPOSITORY https://github.com/lvgl/lvgl.git
# GIT_TAG v8.3.10
# )
# FetchContent_MakeAvailable(lvgl)
# set_target_properties(lvgl PROPERTIES CMAKE_C_STANDARD 11)
# target_compile_options(lvgl PUBLIC -DLV_CONF_PATH=${CMAKE_CURRENT_SOURCE_DIR}/src/lv_conf.h)
# target_link_libraries(${PROJECT_NAME} PUBLIC lvgl)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/docs.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tests.cmake)
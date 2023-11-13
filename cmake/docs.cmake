set(BUILD_ENABLED ${PROJECT_NAME}_GENERATE_DOCS)
string(TOUPPER ${BUILD_ENABLED} BUILD_ENABLED)

option(${BUILD_ENABLED} "build documents option." OFF)

if(${${BUILD_ENABLED}})
    find_package(Doxygen)

    if(DOXYGEN_FOUND)
        set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs)
        doxygen_add_docs(${PROJECT_NAME}_docs "include" ALL)

        install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs/ DESTINATION docs)
    else()
        message(FATAL_ERROR "DOXYGEN EXECUTABLE NOT FOUND!")
    endif()
endif()

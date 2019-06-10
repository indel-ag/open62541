SET(SOURCE_GROUP ${SOURCE_GROUP}\\inos)

ua_add_architecture("inos")

if ((${_index} GREATER -1) OR ("${UA_ARCHITECTURE}" STREQUAL "inos"))

    ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_clock.c)
    ua_add_architecture_file(${CMAKE_CURRENT_SOURCE_DIR}/ua_architecture_functions.c)

    if("${UA_ARCHITECTURE}" STREQUAL "inos")
        ua_include_directories(${CMAKE_CURRENT_SOURCE_DIR})
        ua_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)
        ua_add_architecture_header_beginning(${CMAKE_CURRENT_SOURCE_DIR}/../common/ua_lwip.h)
    endif()
endif()

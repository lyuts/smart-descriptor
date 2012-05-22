cmake_minimum_required (VERSION 2.8)

project (SDTests C CXX)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

include (FindPkgConfig)
pkg_search_module (CPPUNIT REQUIRED cppunit)
pkg_search_module (SQLITE3 REQUIRED sqlite3)
pkg_search_module (LUA REQUIRED lua lua5.1 lua-5.1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPPUNIT_CFLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SQLITE3_CFLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LUA_CFLAGS}")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Weffc++")

add_definitions (
    ${CPPUNIT_CFLAGS_OTHER}
    ${SQLITE3_CFLAGS_OTHER}
    ${LUA_CFLAGS_OTHER}
)

set (BINARY_NAME "SDTests")

### Obtain a list of cpp files
file (GLOB SQLITE3_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/sqlite3/*.cpp")
file (GLOB LUA_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/lua/*.cpp")

set (SDTESTS_SRCS
    ${SQLITE3_SRCS}
    ${LUA_SRCS}
)

add_executable (${BINARY_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${SDTESTS_SRCS})

target_link_libraries (${BINARY_NAME}
    ${CPPUNIT_LIBRARIES}
    ${SQLITE3_LIBRARIES}
    ${LUA_LIBRARIES}
)

include_directories (
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
    ${CPPUNIT_INCLUDEDIR}
    ${SQLITE3_INCLUDEDIR}
    ${LUA_INCLUDEDIR}
)


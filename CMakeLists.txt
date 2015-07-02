cmake_minimum_required (VERSION 2.8)
project (serverlib_test)

add_executable (client client.cpp)
add_executable (server server.cpp)

set (CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra -O2")

find_package (Boost 1.55.0 COMPONENTS
    system
    thread
REQUIRED)

include_directories (/home/bit/src/github/serverlib/libs)

set (libs ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} pthread)

target_link_libraries (client ${libs})
target_link_libraries (server ${libs})

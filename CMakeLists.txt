cmake_minimum_required(VERSION 3.0.2)
project(program)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

file(GLOB SOURCES "*.cpp")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3")
add_executable(program main.cc examplewindow.cc)

target_link_libraries(program ${GTKMM_LIBRARIES})

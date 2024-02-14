cmake_minimum_required(VERSION 3.11)

project(simple-port-scanner CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(Boost 1.78.0 REQUIRED)
find_package(Threads REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(simple_port_scanner  src/main.cpp
        src/scanner/port_scanner.cpp
        src/scanner/port_scanner.h
        src/app/application.cpp)

target_link_libraries(simple_port_scanner PRIVATE
        Threads::Threads
        CONAN_PKG::boost)

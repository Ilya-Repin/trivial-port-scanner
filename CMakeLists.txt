cmake_minimum_required(VERSION 3.11)

project(simple-port-scanner CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

find_package(Boost 1.78.0 REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_library(Scanner STATIC
        src/scanner/port_scanner.cpp
        src/scanner/port_scanner.h
        src/app/application.cpp
        src/app/application.h
        src/util/config_parser/config_parser.cpp
        src/util/config_parser/config_parser.h
        src/util/logger/logger.cpp
        src/util/logger/logger.h
        src/util/program_options/command_line_parser.cpp
        src/util/program_options/command_line_parser.h)


add_executable(simple_port_scanner src/main.cpp)

target_link_libraries(simple_port_scanner PRIVATE
        Scanner
        Threads::Threads
        CONAN_PKG::boost
        fmt::fmt)

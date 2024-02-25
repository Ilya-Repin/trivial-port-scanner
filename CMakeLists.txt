cmake_minimum_required(VERSION 3.11)

project(simple-port-scanner CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(src)

add_library(Logger STATIC
        src/util/logger/logger.cpp
        src/util/logger/logger.h)

target_link_libraries(Logger PRIVATE Threads::Threads CONAN_PKG::boost)

add_library(Scanner STATIC
        src/util/config_parser/config_parser.cpp
        src/util/config_parser/config_parser.h
        src/util/scanning_configs/host_config.h
        src/util/program_options/command_line_parser.cpp
        src/util/program_options/command_line_parser.h
        src/scanner/port_scanner.cpp
        src/scanner/port_scanner.h
        src/app/application.cpp
        src/app/application.h)

target_link_libraries(Scanner PRIVATE Threads::Threads CONAN_PKG::boost CONAN_PKG::fmt)

add_executable(simple_port_scanner src/main.cpp)

target_link_libraries(simple_port_scanner PRIVATE Scanner Logger Threads::Threads CONAN_PKG::boost)

enable_testing()

add_executable(parser_test
        src/util/scanning_configs/host_config.h
        src/util/config_parser/config_parser.h
        src/util/config_parser/config_parser.cpp
        tests/config_parser_tests.cpp)

target_link_libraries(parser_test PRIVATE CONAN_PKG::catch2 Threads::Threads CONAN_PKG::boost Logger)

add_test(NAME PARSER_TEST COMMAND parser_test)
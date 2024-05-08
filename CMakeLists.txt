cmake_minimum_required(VERSION 3.27)
project(libpath
    VERSION 0.1
    LANGUAGES CXX)

add_library(libpath-src SHARED
    src/path/grid.hpp
    src/path/pathfinder.hpp
    src/path/pypath.cpp
)

include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

find_package(Python REQUIRED COMPONENTS Development)

target_compile_features(libpath-src PRIVATE cxx_std_20)
target_include_directories(libpath-src PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Python_INCLUDE_DIRS}
)
message(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(libpath-src PRIVATE pybind11::headers)
set_target_properties(libpath-src PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    PREFIX ""
    OUTPUT_NAME "libpath"
)

pybind11_add_module(libpath src/path/pypath.cpp)


### tests ###
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(libpath-tests
    src/path/pathfinder.test.cpp
)
target_compile_features(libpath-tests PRIVATE cxx_std_20)
target_include_directories(libpath-tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
)
target_link_libraries(libpath-tests PRIVATE Catch2::Catch2WithMain)

add_custom_command(
    TARGET libpath-tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)


### benchmark ###
add_executable(libpath-benchmark
    src/path/pathfinder.bench.cpp
)
target_compile_features(libpath-benchmark PRIVATE cxx_std_20)
target_include_directories(libpath-benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tools
)
target_link_libraries(libpath-benchmark PRIVATE Catch2::Catch2WithMain)

add_custom_command(
    TARGET libpath-benchmark
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
)
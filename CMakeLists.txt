cmake_minimum_required(VERSION 3.28)
project(path_finding
    VERSION 0.1
    LANGUAGES CXX)

add_library(path SHARED
    src/path/grid.hpp
    src/path/navigator.hpp
    src/path/pypath.cpp
)

include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

find_package(Python REQUIRED COMPONENTS Development)

target_compile_features(path PRIVATE cxx_std_20)
target_include_directories(path PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
    ${Python_INCLUDE_DIRS}
)
target_link_libraries(path PRIVATE pybind11::headers)
set_target_properties(path PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

pybind11_add_module(libpath src/path/pypath.cpp)

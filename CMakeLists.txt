cmake_minimum_required(VERSION 3.28)
project(path_finding
    VERSION 0.1
    LANGUAGES CXX)

add_library(path SHARED
    path/Navigator.hpp
    path/Navigator.cpp
    path/Grid.hpp
)
target_compile_features(path PRIVATE cxx_std_20)
target_include_directories(path PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

set_target_properties(path PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

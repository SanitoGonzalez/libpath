cmake_minimum_required(VERSION 3.27)
project(path_finding
    VERSION 0.1
    LANGUAGES CXX)

add_library(path SHARED
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

target_compile_features(path PRIVATE cxx_std_20)
target_include_directories(path PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Python_INCLUDE_DIRS}
)
message(${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(path PRIVATE pybind11::headers)
set_target_properties(path PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

pybind11_add_module(libpath src/path/pypath.cpp)


### tests ###
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.4
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests
    src/path/pathfinder.test.cpp
)
target_compile_features(tests PRIVATE cxx_std_20)
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

enable_testing()
add_test(NAME libpath-tests COMMAND test)
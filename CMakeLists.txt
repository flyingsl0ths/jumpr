cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

include(FetchContent)

set(CMAKE_CXX_EXTENSIONS OFF)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In Source Builds Not Allowed")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
  set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
endif()

set(NAME "jumpr")
set(DESCRIPTION "An \"endless jumper\" game")

project(
  ${NAME}
  VERSION 1.0.0
  DESCRIPTION ${DESCRIPTION}
  LANGUAGES CXX)

add_library(compile-options INTERFACE)

target_compile_options(
  compile-options INTERFACE "-Wextra;-Wall;-Werror;-Wunused-local-typedefs")

target_compile_features(compile-options INTERFACE cxx_std_20)

find_package(SFML 2.5 QUIET COMPONENTS graphics window system audio)

if(NOT SFML_FOUND)
  message(STATUS "SFML not found locally, fetching SFML...")

  FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.1")

  FetchContent_MakeAvailable(sfml)
endif()

add_subdirectory(app)

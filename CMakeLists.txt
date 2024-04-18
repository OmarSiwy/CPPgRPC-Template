cmake_minimum_required(VERSION 3.14)
project(gRPCNvidia)

enable_testing()

# Set C++ Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build the tests." ON)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc")

# Define the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Conditional test building
if(BUILD_TESTS)
  # Add GoogleTest
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  # Add the tests directory
  add_subdirectory(tests)
endif()

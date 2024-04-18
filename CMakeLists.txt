cmake_minimum_required(VERSION 3.14)
project(gRPCNvidia)

enable_testing()

# Set C++ Settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(BUILD_PYTHON "Build the Python bindings." OFF)
option(BUILD_TESTS "Build the tests." ON)

include_directories(inc) # Include
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.cc") # src files, except extension.cc
set(TEST_SOURCES ${SOURCES})
list(FILTER SOURCES EXCLUDE REGEX ".*extension\\.cc$")

# Python Specific Build Library
if (BUILD_PYTHON)
  set (Python_ADDITIONAL_VERSIONS 3)
  find_package (PythonLibs REQUIRED)
  find_package (PythonInterp REQUIRED)

  include_directories("${PYTHON_INCLUDE_DIRS}")
  list(FILTER TEST_SOURCES EXCLUDE REGEX ".*main\\.cc$")

  add_library(core SHARED ${TEST_SOURCES})

  set_target_properties(core PROPERTIES PREFIX "")
  set_target_properties(core PROPERTIES OUTPUT_NAME "gRPCNvidia")

  if (WIN32)
    set_target_properties(core PROPERTIES SUFFIX ".pyd")
  else()
    set_target_properties(core PROPERTIES SUFFIX ".so")
  endif()

  target_link_libraries(core "${PYTHON_LIBRARIES}") # Link Python Libraries
endif()

# If building, this is the main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Conditional Testing
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

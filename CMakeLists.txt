cmake_minimum_required(VERSION 3.25)

project(List LANGUAGES CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define warning flags
set(WAR_PANIC "-Wall -Wextra -pedantic")

# Compiler-specific flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MD /DNDEBUG /Ob2")  # Optimize for MSVC
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd /Zi /RTC1")  # Debugging for MSVC
else()
    set(CMAKE_CXX_FLAGS_RELEASE " ${WAR_PANIC} -O3 -march=native")  # Optimize for GCC/Clang
    set(CMAKE_CXX_FLAGS_DEBUG " ${WAR_PANIC} -O0 -g3 -ggdb")  # Debugging for GCC/Clang
endif()

include_directories("${CMAKE_SOURCE_DIR}/DataStructs")

add_library(List INTERFACE "${CMAKE_SOURCE_DIR}/DataStructs/List.hpp")

# Check if Catch2 directory exists, otherwise use FetchContent
if(EXISTS "${CMAKE_SOURCE_DIR}/Catch2")
    message(STATUS "Using local Catch2")
    add_subdirectory(${CMAKE_SOURCE_DIR}/Catch2)
else()
    message(STATUS "Fetching Catch2 from GitHub")
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0 # or a later release
    )
    FetchContent_MakeAvailable(Catch2)
endif()

# Add executable
add_executable(List_test tests/List.cpp)
target_link_libraries(List_test List Catch2::Catch2WithMain)

enable_testing()
add_test(NAME ListTest COMMAND test)
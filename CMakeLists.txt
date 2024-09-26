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
    target_compile_options(SHA256 PRIVATE)
    set(CMAKE_CXX_FLAGS_RELEASE " ${WAR_PANIC} -O3 -march=native")  # Optimize for GCC/Clang
    set(CMAKE_CXX_FLAGS_DEBUG " ${WAR_PANIC} -O0 -g3 -ggdb")  # Debugging for GCC/Clang
endif()

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/DataStructs")

add_library(List INTERFACE "${CMAKE_SOURCE_DIR}/DataStructs/List.hpp")

# Add executable
add_executable(test src/test.cpp)
target_link_libraries(test List)
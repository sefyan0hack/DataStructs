cmake_minimum_required(VERSION 3.25)

project(DataStructs LANGUAGES CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Clang Tidy
option(USE_CLANG_TIDY "Use clang" OFF)

if(USE_CLANG_TIDY)
     message(STATUS "Using clang-tidy")
     set(CMAKE_CXX_CLANG_TIDY clang-tidy
     --checks=modernize-*,readability-*,performance-*,-modernize-use-trailing-return-type
     --header-filter=.*
     --warnings-as-errors=*
     )
    #  add_compile_options(
    #       -Wunused-variable
    #       -Wunused-function
    #       -Wunused-parameter
    #       -Werror
    #  )
endif()
# Define warning flags
set(WAR_PANIC "-Wall -Wextra -pedantic")

# Compiler-specific flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MD /DNDEBUG /Ob2")  # Optimize for MSVC
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd /fsanitize=address /Zi /RTC1")  # Debugging for MSVC
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${WAR_PANIC} -O3 -march=native")  # Optimize for GCC/Clang
    set(CMAKE_CXX_FLAGS_DEBUG "${WAR_PANIC} -O0 -g3 -ggdb")  # Debugging for GCC/Clang
endif()

set(BUILD_TEST "" ON)


add_subdirectory(${CMAKE_SOURCE_DIR}/DataStructs)
if(BUILD_TEST)
    message( BUILD_TEST " Build Tests ...")
    add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()

enable_testing()
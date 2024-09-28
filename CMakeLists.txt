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
    set(CMAKE_CXX_FLAGS_RELEASE "${WAR_PANIC} -O3 -march=native")  # Optimize for GCC/Clang
    set(CMAKE_CXX_FLAGS_DEBUG "${WAR_PANIC} -O0 -g3 -ggdb")  # Debugging for GCC/Clang
endif()


add_subdirectory(${CMAKE_SOURCE_DIR}/DataStructs)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)


include(CPack)
set(CPACK_GENERATOR "ZIP")

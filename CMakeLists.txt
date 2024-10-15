cmake_minimum_required(VERSION 3.25)

project(DataStructs LANGUAGES CXX)

# Use C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#add CPM as pack man
file(
  DOWNLOAD
  https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.2/CPM.cmake
  ${CMAKE_SOURCE_DIR}/cmake/CPM.cmake
  EXPECTED_HASH SHA256=c8cdc32c03816538ce22781ed72964dc864b2a34a310d3b7104812a5ca2d835d
)

# Define warning flags
set(WAR_PANIC "-Wall -Wextra -pedantic")

# Compiler-specific flags
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /MD /DNDEBUG /Ob2")  # Optimize for MSVC
    set(CMAKE_CXX_FLAGS_DEBUG "/Od /MDd /fsanitize=address /Zi /RTC1")  # Debugging for MSVC
    if (SANITIZE_ADDRESS)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO")
    endif()
    add_compile_options(/wd4005)  # Disable macro redefinition warning
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
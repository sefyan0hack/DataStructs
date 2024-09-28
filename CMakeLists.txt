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

# include_directories("${CMAKE_SOURCE_DIR}/DataStructs")
# add_library(List INTERFACE "${CMAKE_SOURCE_DIR}/DataStructs/List.hpp")

add_subdirectory(${CMAKE_SOURCE_DIR}/DataStructs)
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)




# Add executable
# add_executable(List_test tests/List.cpp)
# target_link_libraries(List_test List Catch2::Catch2WithMain)

# enable_testing()
# add_test(NAME ListTest COMMAND List_test)


# # Specify post-build commands to copy files
# add_custom_command(TARGET List_test POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         $<TARGET_FILE:List_test>
#         "${CMAKE_BINARY_DIR}/build/_CPack_Packages/win32/NSIS/List-0.1.1-win32/"
# )

# Optionally, copy DLLs if your project generates any
# add_custom_command(TARGET List_test POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         "path/to/your/dlls/*.dll"
#         "${CMAKE_BINARY_DIR}/build/_CPack_Packages/win32/NSIS/List-0.1.1-win32/"
# )

include(CPack)
set(CPACK_GENERATOR "ZIP")
# set(CPACK_PACKAGE_NAME "List_test")
# set(CPACK_PACKAGE_VERSION "1.0.0")
# set(CPACK_NSIS_INSTALLER_ICON "${CMAKE_SOURCE_DIR}/icon.ico")  # Optional
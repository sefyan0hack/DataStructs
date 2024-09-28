project(Testing)

include_directories("${CMAKE_SOURCE_DIR}/DataStructs")

if(EXISTS "${CMAKE_SOURCE_DIR}/Catch2")
    message(STATUS "Using local Catch2")
    add_subdirectory("${CMAKE_SOURCE_DIR}/Catch2" "${CMAKE_BINARY_DIR}/Catch2-build")
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
add_executable(List_test "${CMAKE_SOURCE_DIR}/tests/List.cpp")
target_link_libraries(List_test List Catch2::Catch2WithMain)

enable_testing()
add_test(NAME ListTest COMMAND List_test)
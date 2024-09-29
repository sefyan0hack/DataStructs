project(DataStructs)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/DataStructs")

if(EXISTS "${CMAKE_SOURCE_DIR}/Catch2")
    message(STATUS "Using local Catch2")
    add_subdirectory("${CMAKE_SOURCE_DIR}/Catch2" "${CMAKE_BINARY_DIR}/Catch2-build")
else()
    message(STATUS "Fetching Catch2 from GitHub")
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.7.1.zip
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(List_test "${CMAKE_CURRENT_SOURCE_DIR}/List.cpp")

target_link_libraries(List_test List Catch2::Catch2WithMain)

enable_testing()
add_test(NAME ListTest COMMAND List_test)

install(TARGETS List_test DESTINATION tests/bin)

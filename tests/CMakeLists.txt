project(DataStructs)

# include_directories("${CMAKE_CURRENT_SOURCE_DIR}/DataStructs")
set(CATCH2_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE ${CATCH2_BUILD_TYPE} CACHE STRING "Build type" FORCE)
if(EXISTS "${CMAKE_SOURCE_DIR}/Catch2")
    message(STATUS "Using local Catch2")
    add_subdirectory("${CMAKE_SOURCE_DIR}/Catch2" "${CMAKE_BINARY_DIR}/Catch2-build")
	else()
    message(STATUS "Fetching Catch2 from GitHub")
    include(FetchContent)
    set(FETCHCONTENT_QUIET off)
	FetchContent_Declare(Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG devel
	GIT_PROGRESS on
	STAMP_DIR "${${PROJECT_NAME}_BUILD_DIR}"
	DOWNLOAD_NO_PROGRESS off
	LOG_DOWNLOAD on
	LOG_UPDATE on
	LOG_PATCH on
	LOG_CONFIGURE on
	LOG_BUILD on
	LOG_INSTALL off
	LOG_TEST on
	LOG_MERGED_STDOUTERR on
	LOG_OUTPUT_ON_FAILURE on
	USES_TERMINAL_DOWNLOAD on
	)
	FetchContent_MakeAvailable(Catch2)
endif()
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING "Build type" FORCE)  # Restore original build type

add_executable(List_test "${CMAKE_CURRENT_SOURCE_DIR}/List.cpp")

target_include_directories(List_test
    PUBLIC
        $<TARGET_PROPERTY:List,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(List_test List Catch2::Catch2WithMain)

add_test(NAME ListTest COMMAND List_test)

set(ENV{CXXFLAGS} "--coverage")
set(CTEST_USE_LAUNCHERS 1)
set(CTEST_COVERAGE_COMMAND "gcov")
set(CTEST_MEMORYCHECK_COMMAND "valgrind")

set_tests_properties(ListTest PROPERTIES 
         LABELS "unit"  # Add a label for easier selection
)

# You can also set additional properties if needed
set_tests_properties(ListTest PROPERTIES 
         RUN_SERIAL TRUE  # Run tests serially, if necessary
         WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"  # Set working directory
)
include(CTest)


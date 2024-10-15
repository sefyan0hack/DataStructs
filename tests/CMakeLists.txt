include("${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake")
project(DataStructs)

############################################################################################################
#	Include Catch2
############################################################################################################
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
	LOG_PATCH off
	LOG_CONFIGURE on
	LOG_BUILD on
	LOG_INSTALL off
	LOG_TEST off
	LOG_MERGED_STDOUTERR on
	LOG_OUTPUT_ON_FAILURE on
	USES_TERMINAL_DOWNLOAD on
	)
	FetchContent_MakeAvailable(Catch2)
endif()
############################################################################################################
#	add tests
############################################################################################################

New_test_exe(List)
New_test_exe(Stack)

add_test(NAME ListTest COMMAND List_test)
add_test(NAME StackTest COMMAND Stack_test)

set(ENV{CXXFLAGS} "--coverage")
set(CTEST_USE_LAUNCHERS 1)
set(CTEST_COVERAGE_COMMAND "gcov")
set(CTEST_MEMORYCHECK_COMMAND "valgrind")

include(CTest)


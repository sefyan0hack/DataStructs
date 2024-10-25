include("${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
project(DataStructs)

############################################################################################################
#	Include Catch2
############################################################################################################
if(EXISTS "${CMAKE_SOURCE_DIR}/Catch2")
	#if there is "Catch2" (repo) in main dir use it
    message(STATUS "Using local Catch2")
    add_subdirectory("${CMAKE_SOURCE_DIR}/Catch2" "${CMAKE_BINARY_DIR}/Catch2-build")
else()
	CPMAddPackage(
		NAME Catch2
		VERSION 3.7.1
		GITHUB_REPOSITORY catchorg/Catch2
		OPTIONS
			"CATCH_INSTALL_DOCS OFF"
			"CATCH_INSTALL_EXTRAS OFF"
			"CATCH_CONFIG_ENABLE_ALL_STRINGMAKERS OFF"
			"CATCH_BUILD_TESTING OFF"
			"CATCH_DEVELOPMENT_BUILD OFF"
			"CATCH_BUILD_EXAMPLES OFF"
			"CATCH_ENABLE_BENCHMARK OFF"
	)
endif()


############################################################################################################
#	add tests
############################################################################################################

New_test_exe(List)
New_test_exe(Stack)
New_test_exe(Queue)

add_test(NAME ListTest COMMAND List_test)
add_test(NAME StackTest COMMAND Stack_test)
add_test(NAME QueueTest COMMAND Queue_test)

set(ENV{CXXFLAGS} "--coverage")
set(CTEST_USE_LAUNCHERS 1)
set(CTEST_COVERAGE_COMMAND "gcov")
set(CTEST_MEMORYCHECK_COMMAND "valgrind")

include(CTest)


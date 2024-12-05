project(DataStructs)
include("${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Clang Tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

#dont turn Clang tidy for now 
option(USE_CLANG_TIDY "Use clang" OFF)

if(CLANG_TIDY_EXE)
    if(USE_CLANG_TIDY)
        message(STATUS "Using clang-tidy")
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE}
        --checks=modernize-*,readability-*,performance-*,-modernize-use-trailing-return-type,-modernize-use-nodiscard
        --header-filter=.*
        )
    endif()
endif()

#############################################################
# Add Libs
#############################################################
add_LIB(List)
add_LIB(Stack)
add_LIB(Queue)

#############################################################
# Installing
#############################################################
install_tar(List LIST)
install_tar(Stack STACK)
install_tar(Queue QUEUE)

install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include  DESTINATION  .
)
#############################################################
# Packagin
#############################################################

set(CMAKE_DEBUG_POSTFIX "-d")
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_DESCRIPTION "My implimentation of data structs as 2sec  year at FSA (Embeded Systeme)")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/sefyan0hack/DataStructs")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/sefyan0hack/DataStructs")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CMAKE_SYSTEM_NAME}")
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/PACKS")

if(WIN32)
    set(CPACK_GENERATOR "NSIS;ZIP")
elseif(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")
else() 
    set(CPACK_GENERATOR "ZIP")
endif()

include(CPack)
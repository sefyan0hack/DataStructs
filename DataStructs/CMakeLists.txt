project(DataStructs)
include("${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Clang Tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

option(USE_CLANG_TIDY "Use clang" ON)

if(CLANG_TIDY_EXE)
    if(USE_CLANG_TIDY)
        message(STATUS "Using clang-tidy")
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE}
        --checks=modernize-*,readability-*,performance-*,-modernize-use-trailing-return-type,-modernize-use-nodiscard
        --header-filter=.*
        )
        add_compile_options(
            -Wunused-variable
            -Wunused-function
            -Wunused-parameter
        )
    endif()
endif()

#############################################################
# Add Libs
#############################################################
add_LIB(List)
add_LIB(Stack)

#############################################################
# Installing
#############################################################
install_tar(List LIST)
install_tar(List Stack)

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
set(CPACK_PACKAGE_DESCRIPTION "My implimentation of datastructs as 2se  yer at FSA (Embeded System)")
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
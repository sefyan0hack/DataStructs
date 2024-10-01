project(DataStructs)
include("${CMAKE_SOURCE_DIR}/cmake/Scripts.cmake")


#############################################################
# Add Libs
#############################################################
add_library(List INTERFACE)
# target_include_directories(List INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(List INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:lib>"
)


#############################################################
# Installing
#############################################################
install_tar(List LIST)

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
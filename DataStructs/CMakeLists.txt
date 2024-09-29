project(DataStructs)

add_library(List INTERFACE)
target_include_directories(List INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

install(TARGETS List DESTINATION lib)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/List.hpp" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
include(CPack)
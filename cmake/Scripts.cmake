set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/INSTALL" CACHE PATH "Installation directory")

function(install_tar tar_lib tar_Name)
    install(TARGETS ${tar_lib} EXPORT ${tar_Name}
        LIBRARY  DESTINATION lib
    )

    install(EXPORT ${tar_Name}
        FILE "${tar_Name}.cmake"
        NAMESPACE "${tar_Name}::"
        DESTINATION "cmake"
    )
endfunction()

function(add_LIB lib_name)
    add_library(${lib_name} STATIC ${CMAKE_CURRENT_SOURCE_DIR}/${lib_name}.cpp)
    target_include_directories(${lib_name}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # For build tree
            $<INSTALL_INTERFACE:include>                            # For install tree
    )

    message(STATUS "Adding Lib(${lib_name}) : ${CMAKE_CURRENT_SOURCE_DIR}/${lib_name}.cpp")
endfunction()


function(New_test_exe lib_name)
add_executable("${lib_name}_test" "${CMAKE_CURRENT_SOURCE_DIR}/${lib_name}.cpp")

target_include_directories("${lib_name}_test"
    PUBLIC
        $<TARGET_PROPERTY:${lib_name},INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries("${lib_name}_test" ${lib_name} Catch2::Catch2WithMain)
endfunction()

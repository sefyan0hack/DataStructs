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

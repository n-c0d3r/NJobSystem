
function(TargetUseNJS TargetName)

    add_dependencies(${TargetName} NJS)

    target_link_libraries(${TargetName}
        PRIVATE NJS
    )

    target_include_directories(${TargetName}
        PRIVATE ${CMAKE_SOURCE_DIR}/NJS/Source
    )
    
endfunction(TargetUseNJS)



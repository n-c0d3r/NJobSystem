
file(GLOB PublicFiles
    "Source/NJS/*.h"
)
source_group("Source\\NJS\\Public" FILES ${PublicFiles})

file(GLOB PrivateFiles
    "Source/NJS/*.cpp"
)
source_group("Source\\NJS\\Private" FILES ${PrivateFiles})

add_library(NJS
    ${PublicFiles}
    ${PrivateFiles}
)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    target_compile_definitions(NJS
        PUBLIC VCPP = 1
    )
else()

endif()
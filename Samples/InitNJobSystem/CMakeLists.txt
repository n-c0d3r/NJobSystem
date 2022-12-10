
file(GLOB PublicFiles
    "Source/*.h"
)
source_group("Source\\Public" ${PublicFiles})

file(GLOB PrivateFiles
    "Source/*.cpp"
)
source_group("Source\\Private" ${PrivateFiles})

add_executable(Samples.InitNJobSystem
    ${PublicFiles}
    ${PrivateFiles}
)

set_target_properties(Samples.InitNJobSystem
    PROPERTIES 
        FOLDER "Samples"
)

TargetUseNJS(Samples.InitNJobSystem)
cmake_minimum_required(VERSION 3.10)



project(NJobSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)



include(CMake/TargetUseNJS.cmake)



add_subdirectory(NJS)
add_subdirectory(Samples)
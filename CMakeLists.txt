# CMakeList.txt : CMake project for ImageMan, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.19)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

include(FetchContent)

project(kc 
    VERSION 
        1.0 
    DESCRIPTION 
        "C++ scratchpad" 
    LANGUAGES 
        CXX)
    
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) 

add_subdirectory(libs/library)
add_subdirectory(src)
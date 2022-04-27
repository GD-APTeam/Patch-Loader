cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PROJECT_NAME Patch-Loader)
project(${PROJECT_NAME})

find_file(WINDOWS_HEADER windows.h)
if(NOT WINDOWS_HEADER)
    message(FATAL_ERROR "Can't find windows.h!")
endif()

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE libraries/minhook/include)

add_subdirectory(libraries/minhook)
target_link_libraries(${PROJECT_NAME} minhook)
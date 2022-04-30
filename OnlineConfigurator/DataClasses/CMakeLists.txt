#minimum version
cmake_minimum_required(VERSION 3.15)

# common variable for project name and executable name
set(PROJECT_NAME "DataClasses")

#name of a project
project(${PROJECT_NAME})

#where to search headers
include_directories(./interfaces)
include_directories(./include)
include_directories(./include/core)

#set variable where to put ouput file
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set for linker path where libraries are
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,/usr/local/lib")

#set C++ minimum version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set list of files by wildcard into global variable
file(GLOB_RECURSE SRC_FILES "./source/*.cpp")

#create shared library from source
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

#executable needs libraries - so link to installed lisbs
target_link_libraries(${PROJECT_NAME} -luuid)

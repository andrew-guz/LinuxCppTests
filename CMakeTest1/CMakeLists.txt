#minimum version
cmake_minimum_required(VERSION 3.15)

#name of a project
project(CMakeTest1)

#where to search headers
include_directories(./include)

#set variable where to put ouput file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set list of files by wildcard into global variable
file(GLOB SRC_FILES "./source/*.cpp")

#create executable from source
add_executable(CMakeTest1 main.cpp ${SRC_FILES})
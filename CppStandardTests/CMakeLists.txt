#minimum version
cmake_minimum_required(VERSION 3.15)

#allow unit tests
enable_testing()

# common variable for project name and executable name
set(PROJECT_NAME "CppStandardTests")

#build in Debug mode
set(CMAKE_BUILD_TYPE Debug)

#name of a project
project(${PROJECT_NAME})

#where to search headers
include_directories(./include)

#set variable where to put ouput file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#where to search for libraries
link_directories(/usr/local/library)

#set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set C++ minimum version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#this will search for *.cpp in source recursively
file(GLOB_RECURSE SRC_FILES ./source/*.cpp*)

#create executable from source
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

#unit tests section
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/tests)

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)
foreach(TEST_TARGET ${TEST_SOURCES})
    get_filename_component(EXECUTABLE_NAME ${TEST_TARGET} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${TEST_TARGET})
    target_link_libraries(${EXECUTABLE_NAME} Catch2WithMain)
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach()


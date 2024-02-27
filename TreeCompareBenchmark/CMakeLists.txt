#minimum version
cmake_minimum_required(VERSION 3.25)



# common variable for project name and executable name
set(PROJECT_NAME "TreeCompareBenchmark")

#name of a project
project(${PROJECT_NAME})



#check that all needed librarties are preinstalled
function (check_library lib_name)
    find_library(${lib_name}_LIB ${lib_name})
    if(NOT ${lib_name}_LIB)
        message(FATAL_ERROR "${lib_name} library was not found")
    endif()
endfunction()
#check_library(Catch2WithMain)
#check_library(XXX)

#build in Debug or Release mode - see tasks.json
#set(CMAKE_BUILD_TYPE Debug)

#set compiler flags
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")

#set C++ minimum version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




#where to search headers
include_directories(./include)

#set list of files by wildcard into global variable
#file(GLOB SRC_FILES ./source/*.cpp)
#this will search for *.cpp in source recursively
file(GLOB_RECURSE SRC_FILES ./source/*.cpp)

#where to search for libraries
link_directories(/usr/local/library)
link_directories(./../bin/)

#set for linker path where libraries are
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-Wl,-rpath -Wl,/usr/local/lib")

#executable needs libraries - so link to installed lisbs
#target_link_libraries(${PROJECT_NAME} -lwt -lwthttp)


#set variable where to put ouput file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)



#create executable from source
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})
#create shared library from source
#add_library(${PROJECT_NAME} SHARED ${SRC_FILES})


target_link_libraries(${PROJECT_NAME} -lbenchmark -lbenchmark_main)


#allow unit tests
#enable_testing()

#tests
#file(GLOB TEST_SOURCES tests/*.cpp)
#foreach(TEST_TARGET ${TEST_SOURCES})
#    get_filename_component(EXECUTABLE_NAME ${TEST_TARGET} NAME_WE)
#    add_executable(${EXECUTABLE_NAME} ${TEST_TARGET})
#    target_link_libraries(${EXECUTABLE_NAME} Catch2WithMain)
#    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
#endforeach()



#install section
#install(TARGETS ${PROJECT_NAME})
#or
#set(CMAKE_INSTALL_PREFIX /usr/local/bin/XXX)
#install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin/XXX)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/../bin/XXX.json DESTINATION /usr/local/bin/XXX)
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../bin/XXX DESTINATION /usr/local/bin/XXX)
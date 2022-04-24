#minimum version
cmake_minimum_required(VERSION 3.15)

project(OnlineConfigurator)

#subprojects
add_subdirectory(DataClasses)
add_subdirectory(Tests)
add_subdirectory(BackEnd)
add_subdirectory(FrontEnd)

#linkage between projects
target_link_libraries(Tests DataClasses)
target_link_libraries(BackEnd DataClasses)
target_link_libraries(FrontEnd DataClasses)

#minimum version
cmake_minimum_required(VERSION 3.15)

project(OnlineConfigurator)

#subprojects
add_subdirectory (DataClasses)
add_subdirectory (OnlineConfigurator)
add_subdirectory (Tests)

#linkage between projects
target_link_libraries(OnlineConfigurator DataClasses)
target_link_libraries(Tests DataClasses)

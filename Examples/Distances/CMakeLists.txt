cmake_minimum_required (VERSION 2.6)
project (2DTools)


add_executable(Distances main.cpp)
target_link_libraries(Distances ${PROJECT_NAME})
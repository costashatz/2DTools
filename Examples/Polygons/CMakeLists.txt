cmake_minimum_required (VERSION 2.6)
project (2DTools)


add_executable(Polygons main.cpp)
target_link_libraries(Polygons lib${PROJECT_NAME})
cmake_minimum_required (VERSION 2.6)
project (2DTools)


add_executable(VectorsMatrices main.cpp)
target_link_libraries(VectorsMatrices lib${PROJECT_NAME})
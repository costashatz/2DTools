cmake_minimum_required (VERSION 2.6)
project(2DTools)

file(GLOB_RECURSE _srcs
    include/*.h
    include/*.hpp)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fpermissive" )

option(BUILD_TEST "Use Gtest to create the test cases for the code" OFF)

if(BUILD_TEST)
    # Setup testing
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
    enable_testing()
    set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

add_library(lib${PROJECT_NAME} SHARED ${_srcs})
target_include_directories(lib${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
SET_TARGET_PROPERTIES(lib${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

if(BUILD_TEST)
    ##############
    # Unit Tests #
    ##############
    file(GLOB_RECURSE _test_srcs ${PROJECT_SOURCE_DIR}/test/*.cpp)
    add_executable(${PROJECT_TEST_NAME} ${_test_srcs})
    add_dependencies(${PROJECT_TEST_NAME} googletest)

    #target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_NAME})
    target_link_libraries(${PROJECT_TEST_NAME}
                          lib${PROJECT_NAME}
                          ${GTEST_LIBS_DIR}/libgtest.a
                          ${GTEST_LIBS_DIR}/libgtest_main.a
                          pthread)

    # This is so you can do 'make test' to see all your tests run, instead of
    # manually running the executable runUnitTests to see those specific tests.
    add_test(NAME test
             COMMAND ${PROJECT_TEST_NAME})
endif()


add_subdirectory(Examples)
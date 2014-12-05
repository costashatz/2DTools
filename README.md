###Simple Templated Mathematics Library for 2D Graphics

####How to compile:

```
cd path/to/2DTools
mkdir build && cd build
cmake ..
make
```

* Optional CMake options:
	1. BUILD_TEST (ON/OFF) - Determine to either build tests or not. Defaults to OFF.
	2. BUILD_EXAMPLES (ON/OFF) - Specify whether you want to build tests or not. Defaults to OFF.

####How to use:

* You can just edit the CMakeLists.txt and include the headers to your project (after all it is just a header library).
* Via ExternalProject to always get latest edition:
	```cmake
	include(ExternalProject)
	ExternalProject_Add(2DToolsProj
	    GIT_REPOSITORY "https://github.com/costashatz/2DTools"
	    CMAKE_ARGS -DBUILD_TEST=OFF -DBUILD_EXAMPLES=OFF
	    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
	    INSTALL_COMMAND ""
	)
	# Specify include dir
	ExternalProject_Get_Property(2DToolsProj source_dir)
	set(2DTOOLS_INCLUDE_DIRS ${source_dir}/include)

	# Specify MainTest's link libraries
	ExternalProject_Get_Property(2DToolsProj binary_dir)
	set(2DTOOLS_LIBS_DIR ${binary_dir})

	link_directories(${2DTOOLS_LIBS_DIR})
	include_directories(${PROJECT_SOURCE_DIR}/include ${2DTOOLS_INCLUDE_DIRS})
	....
	target_link_libraries(mytarget 2DTools)
	```

####So far I have implemented:

1. Vector2D
    * Simple Class for handling Vectors and Points (maybe needs third component and new class for Points)
2. Matrix1D
    * Simple Class for 2x2 Matrices needed (multiplying with a vector by either side has the same effect)
3. Matrix2D
    * Simple Class for 3x3 Matrices needed (now is column major representation and multiplying with a vector by either side has the same effect)
4. Polygons
    * Simple Classes for Simple Polygon Objects (PolyLine, Polygon2D, Rectanlge, Triangle)
5. LinearShapes
    * Simple Classes for Basic Linear Shapes (Line, Ray, Segment)
6. Distances2D
    * Distances between Polygons and Linear Shapes etc..
7. Simple Unit Tests with gtest

####Planning to implement:

1. Intersections2D
    * Find intersections (intersection area, points, true/false) between all the 2D primitives/shapes above
2. Quadratic Curves
    * Circles
    * Ellipses
3. Polynomial Curves
    * Bezier
    * B-Spline
    * NURBS
4. BSP Trees in 2D
5. Miscellaneous Topics in 2D
    * Convex Hulls
    * Triangulation
    * Area/Volume Measurement

####So far I have tested and are working properly:

1. Vector2D
2. Matrix2D
3. LinearShapes
4. Polygons
5. Distances


####WORK IN PROGRESS - WILL BE UPDATED FREQUENTLY

I am currently working on this little library and will be pushing more updated stuff. Any suggestions of course are more than welcomed.
#include <iostream>
#include <2DTools/Misc/Helper.hpp>
#include <2DTools/Math/Matrix2D.hpp>
#include <2DTools/Distances/Distances2D.hpp>
using namespace std;
using namespace Tools2D;

/**
* Simple Example using Distances function
**/

int main()
{
    Line2d line1 = Line2d(5,2,-3);
    Ray2d ray1 = Ray2d(Vector2d(2,2), Vector2d(1,1));
    Segment2d seg1 = Segment2d(Vector2d(1,1), Vector2d(3,3));
    Segment2d seg2 = Segment2d(Vector2d(1,1), Vector2d(0,2));
	// Create polygon with points: (0,0)->(1,1)->(2,3)->(0,2)->(0,0)
    Polygon2d p1 = Polygon2d();
    p1.AddPoint(Vector2d(0,0));
    p1.AddPoint(Vector2d(1,1));
    p1.AddPoint(Vector2d(2,3));
    p1.AddPoint(Vector2d(0,2));
	//no need to add last point (0,0)
    Vector2d pt1 = Vector2d(2,4);
	cout<<"Distance from line (5*x+2*y-3=0) to Ray (2,2)->(1,1): "<<Distance(line1, ray1)<<endl;
	cout<<"Distance from line (5*x+2*y-3=0) to Segment (1,1)->(3,3): "<<Distance(line1, seg1)<<endl;
	cout<<"Distance from line (5*x+2*y-3=0) to Segment (1,1)->(0,2): "<<Distance(line1, seg2)<<endl;
	cout<<"Distance from point (2,4) to Polygon [(0,0)->(1,1)->(2,3)->(0,2)->(0,0)]: "<<Distance(pt1, p1)<<endl;
	cout<<"Distance from point (2,4) to Ray (2,2)->(1,1): "<<Distance(pt1, ray1)<<endl;
    pt1 = Vector2d(1,0);
	cout<<"Distance from line (5*x+2*y-3=0) to point (1,0): "<<Distance(pt1, line1)<<endl;
    Line2d line2 = Line2d(5,2,-6);
	cout<<"Distance from line (5*x+2*y-3=0) to line (5*x+2*y-6=0): "<<Distance(line1, line2)<<endl;
	return(0);
}

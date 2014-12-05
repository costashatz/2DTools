#include <iostream>
#include <2DTools/Misc/Helper.hpp>
#include <2DTools/Matrix2D.hpp>
#include <2DTools/Distances/Distances2D.hpp>
using namespace std;
using namespace Tools2D;

/**
* Simple Example using Distances function
**/

int main()
{
	Lined line1 = Lined(5,2,-3);
	Rayd ray1 = Rayd(Vector2Dd(2,2), Vector2Dd(1,1));
	Segmentd seg1 = Segmentd(Vector2Dd(1,1), Vector2Dd(3,3));
	Segmentd seg2 = Segmentd(Vector2Dd(1,1), Vector2Dd(0,2));
	// Create polygon with points: (0,0)->(1,1)->(2,3)->(0,2)->(0,0)
	Polygon2Dd p1 = Polygon2Dd();
	p1.AddPoint(Vector2Dd(0,0));
	p1.AddPoint(Vector2Dd(1,1));
	p1.AddPoint(Vector2Dd(2,3));
	p1.AddPoint(Vector2Dd(0,2));
	//no need to add last point (0,0)
	Vector2Dd pt1 = Vector2Dd(2,4);
	cout<<"Distance from line (5*x+2*y-3=0) to Ray (2,2)->(1,1): "<<Distance(line1, ray1)<<endl;
	cout<<"Distance from line (5*x+2*y-3=0) to Segment (1,1)->(3,3): "<<Distance(line1, seg1)<<endl;
	cout<<"Distance from line (5*x+2*y-3=0) to Segment (1,1)->(0,2): "<<Distance(line1, seg2)<<endl;
	cout<<"Distance from point (2,4) to Polygon [(0,0)->(1,1)->(2,3)->(0,2)->(0,0)]: "<<Distance(pt1, p1)<<endl;
	cout<<"Distance from point (2,4) to Ray (2,2)->(1,1): "<<Distance(pt1, ray1)<<endl;
	pt1 = Vector2Dd(1,0);
	cout<<"Distance from line (5*x+2*y-3=0) to point (1,0): "<<Distance(pt1, line1)<<endl;
	Lined line2 = Lined(5,2,-6);
	cout<<"Distance from line (5*x+2*y-3=0) to line (5*x+2*y-6=0): "<<Distance(line1, line2)<<endl;
	return(0);
}

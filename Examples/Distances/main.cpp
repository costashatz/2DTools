#include <iostream>
#include "helper.h"
#include "Matrix2D.h"
#include "Distances2D.h"
using namespace std;

/**
* Simple Example using Distances function
**/

int main()
{
	Line line1 = Line(5,2,-3);
	Ray ray1 = Ray(Vector2D(2,2), Vector2D(1,1));
	Segment seg1 = Segment(Vector2D(1,1), Vector2D(3,3));
	Segment seg2 = Segment(Vector2D(1,1), Vector2D(0,2));
	// Create polygon with points: (0,0)->(1,1)->(2,3)->(0,2)->(0,0)
	Polygon2D p1 = Polygon2D();
	p1.AddPoint(Vector2D(0,0));
	p1.AddPoint(Vector2D(1,1));
	p1.AddPoint(Vector2D(2,3));
	p1.AddPoint(Vector2D(0,2));
	//no need to add last point (0,0)
	Vector2D pt1 = Vector2D(2,4);
	cout<<"Distance from line (5*x+2*y-3=0) to Ray (2,2)->(1,1): "<<Distance(line1, ray1)<<endl;
	cout<<"Distance from line (5*x+2*y-3=0) to Segment (1,1)->(3,3): "<<Distance(line1, seg1)<<endl;
	cout<<"Distance from line (5*x+2*y-3=0) to Segment (1,1)->(0,2): "<<Distance(line1, seg2)<<endl;
	cout<<"Distance from point (2,4) to Polygon [(0,0)->(1,1)->(2,3)->(0,2)->(0,0)]: "<<Distance(pt1, p1)<<endl;
	cout<<"Distance from point (2,4) to Ray (2,2)->(1,1): "<<Distance(pt1, ray1)<<endl;
	pt1 = Vector2D(1,0);
	cout<<"Distance from line (5*x+2*y-3=0) to point (1,0): "<<Distance(pt1, line1)<<endl;
	Line line2 = Line(5,2,-6);
	cout<<"Distance from line (5*x+2*y-3=0) to line (5*x+2*y-6=0): "<<Distance(line1, line2)<<endl;
	return(0);
}

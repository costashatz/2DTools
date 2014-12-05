#include <iostream>
#include <2DTools/Misc/Helper.hpp>
#include <2DTools/Math/Matrix2D.hpp>
#include <2DTools/Primitives/LinearShapes.hpp>
using namespace std;
using namespace Tools2D;

/**
* Simple Example using LinearShape (Line,Ray,Segment) classes
**/

int main()
{
    Line2d line1 = Line2d(5,2,-3);
	cout<<line1.a()<<"*x + "<<line1.b()<<"*y + "<<line1.c()<<" = 0"<<endl;
	cout<<"Equivalently: \n";
	cout<<"P=("<<line1.P().X()<<" "<<line1.P().Y()<<"), Dir=("<<line1.D().X()<<" "<<line1.D().Y()<<")\n";
    Ray2d ray1 = Ray2d(Vector2d(0,0), Vector2d(1,1));
	cout<<"Ray with starting point: ("<<ray1.P().X()<<" "<<ray1.P().Y()<<") and Dir: ("<<ray1.D().X()<<" "<<ray1.D().Y()<<")\n";
	cout<<"Equivalently (in line equation - not all points of this line are on the ray): \n";
	cout<<ray1.a()<<"*x + "<<ray1.b()<<"*y + "<<ray1.c()<<" = 0"<<endl;
    Segment2d seg1 = Segment2d(Vector2d(1,1), Vector2d(3,3));
	cout<<"Segment from ("<<seg1.P0().X()<<" "<<seg1.P0().Y()<<") to ("<<seg1.P1().X()<<" "<<seg1.P1().Y()<<"): \n";
	cout<<"Has length: "<<seg1.Length()<<endl;
	cout<<"In line equation (not all points of this line are on the segment): \n";
	cout<<seg1.a()<<"*x + "<<seg1.b()<<"*y + "<<seg1.c()<<" = 0"<<endl;
	return(0);
}

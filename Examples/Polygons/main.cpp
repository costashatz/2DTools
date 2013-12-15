#include <iostream>
#include "helper.h"
#include "Matrix2D.h"
#include "Distances2D.h"
using namespace std;

/**
* Simple Example using Polygon classes
**/

int main()
{
	// Create triangle with vertices (0,0)->(1,1)->(0,1)->(0,0) [last edge is assumed, no need to be given]
	Triangle2D t1 = Triangle2D(Vector2D(0,0), Vector2D(1,1), Vector2D(0,1));
	cout<<"Triangle has vertices:\n";
	for(int i=0;i<t1.Vertices().size();i++)
	{
		cout<<"("<<t1.Vertices()[i].X()<<" "<<t1.Vertices()[i].Y()<<") ";
	}
	cout<<"\nIt is ";
	if(t1.Convex())
		cout<<"convex, ";
	else
		cout<<"non-convex, ";
	if(t1.ClockwiseOrdered())
		cout<<"clockwise ordered ";
	else
		cout<<"counter-clockwise ordered ";
	cout<<"with area = "<<t1.Area()<<endl;
	// Create rectangle with bottom-left point (0,0) and edges (2,0) and (0,1)
	Rectangle2D r1 = Rectangle2D(Vector2D(0,0), Vector2D(2,0), Vector2D(0,1));
	cout<<"\nRectangle has vertices:\n";
	for(int i=0;i<r1.Vertices().size();i++)
	{
		cout<<"("<<r1.Vertices()[i].X()<<" "<<r1.Vertices()[i].Y()<<") ";
	}
	cout<<"\nIt is ";
	if(r1.Convex())
		cout<<"convex, ";
	else
		cout<<"non-convex, ";
	if(r1.ClockwiseOrdered())
		cout<<"clockwise ordered ";
	else
		cout<<"counter-clockwise ordered ";
	cout<<"with area = "<<r1.Area()<<endl;
	// Create polygon with points: (0,0)->(1,1)->(2,3)->(0,2)->(0,0)
	Polygon2D p1 = Polygon2D();
	p1.AddPoint(Vector2D(0,0));
	p1.AddPoint(Vector2D(1,1));
	p1.AddPoint(Vector2D(2,3));
	p1.AddPoint(Vector2D(0,2));
	//no need to add last point (0,0)
	cout<<"\nPolygon p1 has vertices:\n";
	for(int i=0;i<p1.Vertices().size();i++)
	{
		cout<<"("<<p1.Vertices()[i].X()<<" "<<p1.Vertices()[i].Y()<<") ";
	}
	cout<<"\nIt is ";
	if(p1.Convex())
		cout<<"convex, ";
	else
		cout<<"non-convex, ";
	if(p1.ClockwiseOrdered())
		cout<<"clockwise ordered ";
	else
		cout<<"counter-clockwise ordered ";
	cout<<"with area = "<<p1.Area()<<endl;
	// Create polygon with points: (0,0)->(2,2)->(0,2)->(2,0)->(0,0)
	// it is clearly non-convex (concave)
	Polygon2D p2 = Polygon2D();
	p2.AddPoint(Vector2D(0,0));
	p2.AddPoint(Vector2D(2,2));
	p2.AddPoint(Vector2D(0,2));
	p2.AddPoint(Vector2D(2,0));
	//no need to add last point (0,0)
	cout<<"\nPolygon p2 has vertices:\n";
	for(int i=0;i<p2.Vertices().size();i++)
	{
		cout<<"("<<p2.Vertices()[i].X()<<" "<<p2.Vertices()[i].Y()<<") ";
	}
	cout<<"\nIt is ";
	if(p2.Convex())
		cout<<"convex, ";
	else
		cout<<"non-convex, ";
	if(p2.ClockwiseOrdered())
		cout<<"clockwise ordered ";
	else
		cout<<"counter-clockwise ordered ";
	cout<<"with area (this method gives no/bad information for non-convex polygons) = "<<p2.Area()<<endl;
	return(0);
}

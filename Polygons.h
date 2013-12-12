#ifndef POLYGONS_H
#define POLYGONS_H
#include "LinearShapes.h"
#include <vector>
using namespace std;

//assuming edges are 0->1->2->3..etc
class Polyline2D
{
protected:
	vector<Vector2D> vertices;
public:
	Polyline2D()
	{
		vertices = vector<Vector2D>();
	}

	virtual void AddPoint(const Vector2D& point)
	{
		vertices.push_back(point);
	}

	vector<Vector2D> Vertices() {return vertices;}
};

class Polygon2D: public Polyline2D
{
public:
	Polygon2D():Polyline2D(){}

	virtual double Area() //gives correct answer if polygon is simple (=non-adjacent segments do not intersect)
	{
		double sum = 0.0;
		for(int i=0;i<vertices.size()-1;i++)
		{
			sum += vertices[i].X()*vertices[i+1].Y()-vertices[i].Y()*vertices[i+1].X();
		}
		sum /= 2.0;
		return abs(sum);
	}

	bool ClockwiseOrdered()
	{
		//clockwise (sum<0)
		double sum = 0.0;
		for(int i=0;i<vertices.size()-1;i++)
		{
			sum += vertices[i].X()*vertices[i+1].Y()-vertices[i].Y()*vertices[i+1].X();
		}
		if(sum < 0)
			return true;
		return false;
	}

	bool Convex()
	{
		//convex (all cross products same sign)
		int plus=0,minus=0;
		for(int i=1;i<vertices.size()-1;i++)
		{
			if(((vertices[i].X()-vertices[i-1].X())*(vertices[i+1].Y()-vertices[i].Y())-(vertices[i].Y()-vertices[i-1].Y())*(vertices[i+1].X()-vertices[i].X()))<0)
				minus++;
			else
				plus++;
			if(plus>0&&minus>0)
				break;
		}
		if(plus>0&&minus>0)
			return false;
		return true;
	}
};

class Triangle2D: public Polygon2D
{
public:
	Triangle2D(Vector2D p0, Vector2D p1, Vector2D p2):Polygon2D()
	{
		Polygon2D::AddPoint(p0);
		Polygon2D::AddPoint(p1);
		Polygon2D::AddPoint(p2);
	}

	void AddPoint(Vector2D point)
	{
		return;
	}
};

class Rectangle2D: public Polygon2D
{
public:
	Rectangle2D(Vector2D p0, Vector2D e0, Vector2D e1):Polygon2D()
	{
		if((e0*e1)!=0)
			e1 = e0.Perp();
		Polygon2D::AddPoint(p0);
		Polygon2D::AddPoint(p0+e0);
		Polygon2D::AddPoint(p0+e0+e1);
		Polygon2D::AddPoint(p0+e1);
	}

	Rectangle2D(Vector2D p, double a, double b) //creates rectangle axis aligned (p = center of rectangle,a=length of x edge,b=length of y edge)
	{
		Vector2D p0 = Vector2D(p.X()-a/2.0, p.Y()-b/2.0);
		Polygon2D::AddPoint(p0);
		Vector2D p1 = Vector2D(p.X()+a/2.0, p.Y()-b/2.0);
		Polygon2D::AddPoint(p1);
		Vector2D p2 = Vector2D(p.X()+a/2.0, p.Y()+b/2.0);
		Polygon2D::AddPoint(p2);
		Vector2D p3 = Vector2D(p.X()-a/2.0, p.Y()+b/2.0);
		Polygon2D::AddPoint(p3);
	}

	void AddPoint(Vector2D point)
	{
		return;
	}
};

#endif
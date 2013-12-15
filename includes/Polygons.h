#ifndef POLYGONS_H
#define POLYGONS_H

/**
* Includes
**/
#include "LinearShapes.h"
#include <vector>
using namespace std;


/**
* Polyline2D Class
* Polyline is a collection of arbitrary segments (or points)
* I use the form of collection of points..Edges are assumed to be P0->P1->P2->...->Pn
**/
class Polyline2D
{
protected:
	// Collection of points (called vertices)
	vector<Vector2D> vertices;
public:
	/**
	* Default Constructor
	* Initialization
	**/
	Polyline2D()
	{
		vertices = vector<Vector2D>();
	}

	/**
	* Add new point to the polyline
	* virtual method - can be overwritten by subclasses
	* @param point - point to be added
	**/
	virtual void AddPoint(const Vector2D& point)
	{
		vertices.push_back(point);
	}

	/**
	* Get Vertices/Points
	* @return vector<Vector2D> - the collection of points/vertices
	**/
	vector<Vector2D> Vertices() {return vertices;}
};

/**
* Polygon2D Class
* Polygon is a closed Polyline (closed means the first and the last points are the same)
* Assumes there is an extra point in the end identical to the first one
**/
class Polygon2D: public Polyline2D
{
public:
	/**
	* Default Constructor
	* Initialization
	**/
	Polygon2D():Polyline2D(){}

	/**
	* Get the area under the polygon
	* gives correct answer if polygon is simple/convex (=non-adjacent segments do not intersect)
	* @return double - the area
	**/
	virtual double Area()
	{
		double sum = 0.0;
		for(int i=0;i<vertices.size()-1;i++)
		{
			sum += vertices[i].X()*vertices[i+1].Y()-vertices[i].Y()*vertices[i+1].X();
		}
		sum /= 2.0;
		return abs(sum);
	}

	/**
	* Check if vertices/points are clockwise ordered or not
	* @return bool - a boolean indicating if points are clockwise ordered
	**/
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

	/**
	* Check if polygon is convex
	* @return bool - a boolean indicating whether the polygon is convex
	**/
	bool Convex()
	{
		//convex (all cross products same sign)
		int plus=0,minus=0;
		for(int i=1;i<vertices.size();i++)
		{
			int ind = (i+1)%vertices.size();
			if(((vertices[i].X()-vertices[i-1].X())*(vertices[ind].Y()-vertices[i].Y())-(vertices[i].Y()-vertices[i-1].Y())*(vertices[ind].X()-vertices[i].X()))<0)
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

/**
* Triangle2D Class
**/
class Triangle2D: public Polygon2D
{
public:
	/**
	* Constructor
	* @param p0 - the first point of the triangle
	* @param p1 - the second point of the triangle
	* @param p2 - the third point of the triangle
	**/
	Triangle2D(Vector2D p0, Vector2D p1, Vector2D p2):Polygon2D()
	{
		Polygon2D::AddPoint(p0);
		Polygon2D::AddPoint(p1);
		Polygon2D::AddPoint(p2);
	}

	/**
	* Overwrite virtual method AddPoint so that it does nothing
	* We do not want other points to be added in a triangle
	**/
	void AddPoint(const Vector2D& point)
	{
		return;
	}
};

/**
* Rectangle2D Class
**/
class Rectangle2D: public Polygon2D
{
public:
	/**
	* Constructor
	* @param p0 - lower left point of rectangle
	* @param e0 - direction (with length) of horizontal edge
	* @param e1 - direction (with length) of vertical edge
	**/
	Rectangle2D(Vector2D p0, Vector2D e0, Vector2D e1):Polygon2D()
	{
		if((e0*e1)!=0)
			e1 = e0.Perp();
		Polygon2D::AddPoint(p0);
		Polygon2D::AddPoint(p0+e0);
		Polygon2D::AddPoint(p0+e0+e1);
		Polygon2D::AddPoint(p0+e1);
	}

	/**
	* Constructor
	* creates axis aligned rectangle
	* @param p - center of the rectangle
	* @param a - length of horizontal edge
	* @param b - length of vertical edge
	**/
	Rectangle2D(Vector2D p, double a, double b)
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

	/**
	* Overwrite virtual method AddPoint so that it does nothing
	* We do not want other points to be added in a triangle
	**/
	void AddPoint(const Vector2D& point)
	{
		return;
	}
};

#endif
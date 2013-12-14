#ifndef LINEAR_SHAPES_H
#define LINEAR_SHAPES_H

/**
* Includes
**/
#include "Vector2D.h"

/**
* Base Class for Linear Shapes
* I have used the parametric form of linear shape: X(t) = P+t*d, P=point, d=direction vector, t=parameter
* I have also provided methods to "convert" to implicit form (a*x+b*y+c=0)
* Conversion equations (from parametric to implicit): a=-d.Y(), b=d.X(), c=P.X()*d.Y()-P.Y()*d.X()
* Conversion equations (from implicit to parametric): d=(-b,a), p=(1/(a^2+b^2))(-a*c,-b*c), a*P.X()+b*P.Y()=c
**/
class LinearShape
{
protected:
	// LinearShape data
	Vector2D p;
	Vector2D d;
public:
	/**
	* Default Constructor
	* Initializes both p and d to zero vectors
	**/
	LinearShape():p(Vector2D()),d(Vector2D()){}

	/**
	* Constructor - Parametric Form
	* @param P - point P
	* @param D - direction vector d
	**/
	LinearShape(Vector2D P, Vector2D D):p(P),d(D){}

	/**
	* Copy Constructor
	* @param other - LinearShape to copy from
	**/
	LinearShape(const LinearShape& other)
	{
		this->p = Vector2D(other.p);
		this->d = Vector2D(other.d);
	}

	/**
	* Get Point P - Parametric Form
	* @return Vector2D - the Point p
	**/
	Vector2D P()const {return p;}

	/**
	* Get Direction Vector d - Parametric Form
	* @return Vector2D - the direction vector
	**/
	Vector2D D()const {return d;}

	/**
	* Get "a" value - Implicit Form
	* @return double - the "a" value
	**/
	double a() {return -d.Y();}

	/**
	* Get "b" value - Implicit Form
	* @return double - the "b" value
	**/
	double b() {return d.X();}

	/**
	* Get "c" value - Implicit Form
	* @return double - the "c" value
	**/
	double c() {return (p.X()*d.Y()-p.Y()*d.X());}

	/**
	* Get Normal of Line
	* @return Vector2D - the Normal vector
	**/
	Vector2D n() {return Vector2D(a(),b());}
};

/**
* Line Class
* A line is a linear shape with no restrictions on "t" value of the parametric form
**/
class Line: public LinearShape
{
public:
	/**
	* Default Constructor
	**/
	Line():LinearShape(){}

	/**
	* Constructor - Parametric Form
	* @param P - point P
	* @param D - direction vector d
	**/
	Line(Vector2D P, Vector2D D):LinearShape(P,D){}

	/**
	* Constructor - Implicit Form
	* @param a - "a" value
	* @param b - "b" value
	* @param c - "c" value
	**/
	Line(double a, double b, double c):LinearShape()
	{
		d = Vector2D(-b,a);
		p = Vector2D(-a*c,-b*c);
		p /= (a*a+b*b);
	}

	/**
	* Constructor - Via Normal Vector
	* @param n - Normal Vector
	* @param d - "d" value
	**/
	Line(Vector2D n, double d)
	{
		Line(n.X(),n.Y(),-d);
	}
};


/**
* Ray Class
* A ray is a linear shape with t>=0 (parametric form)
**/
class Ray: public LinearShape
{
public:
	/**
	* Default Constructor
	**/
	Ray():LinearShape(){}

	/**
	* Constructor - A ray is defined by a starting point P and a direction D
	* @param P - point P
	* @param D - direction vector d
	**/
	Ray(Vector2D P, Vector2D D):LinearShape(P,D){}
};


/**
* Segment Class
* A segment is a linear shape with tE[0,1] (parametric form)
**/
class Segment: public LinearShape
{
public:
	/**
	* Default Constructor
	**/
	Segment():LinearShape(){}

	/**
	* Constructor - A segment is defined by two points (P0-starting point, P1-ending point)
	* @param P0 - starting point
	* @param P1 - ending point
	**/
	Segment(Vector2D P0, Vector2D P1):LinearShape(P0, P1-P0){}


	/**
	* Get Starting Point P0 - Is exactly the same as P() - I've included for clarity/completeness
	* @return Vector2D - the Starting Point P0
	**/
	Vector2D P0()const {return p;}


	/**
	* Get Ending Point P1
	* @return Vector2D - the Ending Point P1
	**/
	Vector2D P1()const {return p+d;}

	/**
	* Get Length of Segment
	* @return double - length of segment
	**/
	double Length()const { return d.Length();}

	/**
	* Get Length Squared of Segment
	* @return double - length squared of segment
	**/
	double LengthSq()const { return d.LengthSq();}
};


#endif
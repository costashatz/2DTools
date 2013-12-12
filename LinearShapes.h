#ifndef LINEAR_SHAPES_H
#define LINEAR_SHAPES_H
#include "Vector2D.h"

//ax+by+c=0=>d=(-b,a), p=(1/(a^2+b^2))(-ac,-bc) || aPx+bPy=c

//x = P+td, P=point, d=vector
class LinearShape
{
protected:
	Vector2D p;
	Vector2D d;
public:
	LinearShape():p(Vector2D()),d(Vector2D()){}
	LinearShape(Vector2D P, Vector2D D):p(P),d(D){}

	Vector2D P()const {return p;}
	Vector2D D()const {return d;}
	double a() {return d.Y();}
	double b() {return -d.X();}
	double c() {return a()*p.X()+b()*p.Y();}
	Vector2D n() {return Vector2D(a(),b());}
};

class Line: public LinearShape
{
public:
	Line():LinearShape(){}
	Line(Vector2D P, Vector2D D):LinearShape(P,D){}
	Line(double a, double b, double c):LinearShape()
	{
		d = Vector2D(-b,a);
		p = Vector2D(-a*c,-b*c);
		p /= (a*a+b*b);
	}
	Line(Vector2D n, double d):LinearShape()
	{
		//n = (a,b), d=-c
		double a = n.X();
		double b = n.Y();
		double c = -d;
		this->d = Vector2D(-b, a);
		p = Vector2D(-a*c,-b*c);
		p /= (a*a+b*b);
	}
};


//t>=0
class Ray: public LinearShape
{
public:
	Ray():LinearShape(){}
	Ray(Vector2D P, Vector2D D):LinearShape(P,D){}
};


//tE[0,1]
class Segment: public LinearShape
{
public:
	Segment():LinearShape(){}
	Segment(Vector2D P0, Vector2D P1):LinearShape(P0, P1-P0){}

	Vector2D P1() {return p+d;}
};


#endif
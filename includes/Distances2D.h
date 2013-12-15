#ifndef DISTANCES_2D_H
#define DISTANCES_2D_H

/**
* Includes
**/
#include "Polygons.h"


/**
* Computes Point to Line Distance Squared
* @param point
* @param line
**/
double DistanceSq(Vector2D point, Line line)
{
	Vector2D n = line.n();
	double distance = abs(n*point-line.c())/n.Length();
	return (distance*distance);
}

/**
* Computes Point to Line Distance
* @param point
* @param line
**/
double Distance(Vector2D point, Line line)
{
	Vector2D n = line.n();
	return (abs(n*point-line.c())/n.Length());
}



/**
* Computes Point to Ray Distance Squared
* @param point
* @param ray
**/
double DistanceSq(Vector2D point, Ray ray)
{
	Vector2D toP = point-ray.P();
	if((ray.D()*toP)>0)
		return DistanceSq(point,Line(ray.P(), ray.D()));
	return toP.LengthSq();
}

/**
* Computes Point to Ray Distance
* @param point
* @param ray
**/
double Distance(Vector2D point, Ray ray)
{
	Vector2D toP = point-ray.P();
	if((ray.D()*toP)>0)
		return Distance(point,Line(ray.P(), ray.D()));
	return toP.Length();
}



/**
* Computes Point to Segment Distance Squared
* @param point
* @param seg
**/
double DistanceSq(Vector2D point, Segment seg)
{
	Vector2D D = seg.D();
	Vector2D toP = point-seg.P();
	double t = D*toP;
	if(t<=0)
	{
		return toP.LengthSq();
	}
	double DdD = D.LengthSq();
	if(t>=DdD)
	{
		Vector2D toP1 = point-seg.P1();
		return toP1.LengthSq();
	}
	return DistanceSq(point, Line(seg.P(), seg.D()));
}

/**
* Computes Point to Segment Distance
* @param point
* @param seg
**/
double Distance(Vector2D point, Segment seg)
{
	Vector2D D = seg.D();
	Vector2D toP = point-seg.P();
	double t = D*toP;
	if(t<=0)
	{
		return toP.Length();
	}
	double DdD = D.LengthSq();
	if(t>=DdD)
	{
		Vector2D toP1 = point-seg.P1();
		return toP1.Length();
	}
	return Distance(point, Line(seg.P(), seg.D()));
}



/**
* Computes Point to Polyline Distance Squared
* @param point
* @param line
**/
double DistanceSq(Vector2D point, Polyline2D line)
{
	double m = DistanceSq(point, Segment(line.Vertices()[0], line.Vertices()[1]));
	Vector2D prev = line.Vertices()[1];
	double prevX = prev.X()-point.X();
	double prevY = prev.Y()-point.Y();
	double currX, currY;
	for(int i=1;i<line.Vertices().size()-1;i++)
	{
		currX = line.Vertices()[i+1].X()-point.X();
		currY = line.Vertices()[i+1].X()-point.X();
		if((prevX*prevX <= m && currX*currX <= m && (prevX*currX)>0) && (prevY*prevY <= m && currY*currY <= m && (prevY*currY)>0))
		{
			m = DistanceSq(point, Segment(line.Vertices()[i], line.Vertices()[i+1]));
		}
		prevX = currX;
		prevY = currY;
	}
	return m;
}

/**
* Computes Point to Polyline Distance
* @param point
* @param line
**/
double Distance(Vector2D point, Polyline2D line)
{
	double m = Distance(point, Segment(line.Vertices()[0], line.Vertices()[1]));
	Vector2D prev = line.Vertices()[1];
	double prevX = abs(prev.X()-point.X());
	double prevY = abs(prev.Y()-point.Y());
	double currX, currY;
	for(int i=1;i<line.Vertices().size()-1;i++)
	{
		currX = abs(line.Vertices()[i+1].X()-point.X());
		currY = abs(line.Vertices()[i+1].X()-point.X());
		if((prevX <= m && currX <= m && (prevX*currX)>0) && (prevY <= m && currY <= m && (prevY*currY)>0))
		{
			m = Distance(point, Segment(line.Vertices()[i], line.Vertices()[i+1]));
		}
		prevX = currX;
		prevY = currY;
	}
	return m;
}


//LINE-LINE
double DistanceSq(Line line1, Line line2)
{
	Vector2D d2P = line2.D().Perp2();
	if(line1.D()*d2P!=0)
		return 0.0;
	Vector2D d1P = line1.D().Perp2();
	double a = d1P*(line2.P()-line1.P());
	return (a*a)/line1.D().LengthSq();
}


double Distance(Line line1, Line line2)
{
	Vector2D d2P = line2.D().Perp2();
	if(line1.D()*d2P!=0)
		return 0.0;
	Vector2D d1P = line1.D().Perp2();
	double a = abs(d1P*(line2.P()-line1.P()));
	return a/line1.D().Length();
}

//LINE-RAY
double DistanceSq(Line line, Ray ray)
{
	Vector2D n0 = line.n();
	double c0 = -line.c();
	if((n0*ray.D())*(n0*ray.P()-c0)<0)
		return 0.0;
	double a = n0*ray.P()-c0;
	return ((a*a)/n0.LengthSq());
}

double Distance(Line line, Ray ray)
{
	Vector2D n0 = line.n();
	double c0 = -line.c();
	if((n0*ray.D())*(n0*ray.P()-c0)<0)
		return 0.0;
	return (abs(n0*ray.P()-c0)/n0.Length());
}

//LINE-SEGMENT
double DistanceSq(Line line, Segment seg)
{
	Vector2D Q0 = seg.P();
	Vector2D Q1 = seg.P1();
	double c = -line.c();
	Vector2D n = line.n();
	double a = (n*Q0-c);
	double b = (n*Q1-c);
	if(a*b<0)
		return 0.0;
	a = a*a;
	a /= n.LengthSq();
	b = b*b;
	b /= n.LengthSq();
	return min(a,b);
}

double Distance(Line line, Segment seg)
{
	Vector2D Q0 = seg.P();
	Vector2D Q1 = seg.P1();
	double c = -line.c();
	Vector2D n = line.n();
	double a = (n*Q0-c);
	double b = (n*Q1-c);
	if(a*b<0)
		return 0.0;
	a /= n.Length();
	b /= n.Length();
	return min(abs(a),abs(b));
}

//RAY-RAY

#endif
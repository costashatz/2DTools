#ifndef DISTANCES_2D_H
#define DISTANCES_2D_H

/**
* Includes
**/
#include <2DTools/Misc/Helper.hpp>
#include <2DTools/Primitives/Polygons.hpp>


namespace Tools2D {

/**
* Computes Point to Line Distance Squared
* @param point
* @param line
**/
template<class T>
double DistanceSq(Vector2D<T> point, Line<T> line)
{
    Vector2D<T> n = line.n();
    double distance = std::abs(n*point+line.c())/n.Length();
    return (distance*distance);
}

template<class T>
double DistanceSq(Line<T> line, Vector2D<T> point)
{
    return DistanceSq(point,line);
}

/**
* Computes Point to Line Distance
* @param point
* @param line
**/
template<class T>
double Distance(Vector2D<T> point, Line<T> line)
{
    Vector2D<T> n = line.n();
    return (std::abs(n*point+line.c())/n.Length());
}

template<class T>
double Distance(Line<T> line, Vector2D<T> point)
{
    return Distance(point,line);
}

/**
* Computes Point to Ray Distance Squared
* @param point
* @param ray
**/
template<class T>
double DistanceSq(Vector2D<T> point, Ray<T> ray)
{
    Vector2D<T> toP = point-ray.P();
    if((ray.D()*toP)>0)
        return DistanceSq(point,Line<T>(ray.P(), ray.D()));
    return toP.LengthSq();
}

template<class T>
double DistanceSq(Ray<T> ray, Vector2D<T> point)
{
    return DistanceSq(point,ray);
}

/**
* Computes Point to Ray Distance
* @param point
* @param ray
**/
template<class T>
double Distance(Vector2D<T> point, Ray<T> ray)
{
    Vector2D<T> toP = point-ray.P();
    if((ray.D()*toP)>0)
        return Distance(point,Line<T>(ray.P(), ray.D()));
    return toP.Length();
}

template<class T>
double Distance(Ray<T> ray, Vector2D<T> point)
{
    return Distance(point,ray);
}


/**
* Computes Point to Segment Distance Squared
* @param point
* @param seg
**/
template<class T>
double DistanceSq(Vector2D<T> point, Segment<T> seg)
{
    Vector2D<T> D = seg.D();
    Vector2D<T> toP = point-seg.P();
    double t = D*toP;
    if(t<=0)
    {
        return toP.LengthSq();
    }
    double DdD = D.LengthSq();
    if(t>=DdD)
    {
        Vector2D<T> toP1 = point-seg.P1();
        return toP1.LengthSq();
    }
    return DistanceSq(point, Line<T>(seg.P(), seg.D()));
}

template<class T>
double DistanceSq(Segment<T> seg, Vector2D<T> point)
{
    return DistanceSq(point,seg);
}

/**
* Computes Point to Segment Distance
* @param point
* @param seg
**/
template<class T>
double Distance(Vector2D<T> point, Segment<T> seg)
{
    Vector2D<T> D = seg.D();
    Vector2D<T> toP = point-seg.P();
    double t = D*toP;
    if(t<=0)
    {
        return toP.Length();
    }
    double DdD = D.LengthSq();
    if(t>=DdD)
    {
        Vector2D<T> toP1 = point-seg.P1();
        return toP1.Length();
    }
    return Distance(point, Line<T>(seg.P(), seg.D()));
}

template<class T>
double Distance(Segment<T> seg, Vector2D<T> point)
{
    return Distance(point,seg);
}


/**
* Computes Point to Polyline Distance Squared
* @param point
* @param line
**/
template<class T>
double DistanceSq(Vector2D<T> point, Polyline2D<T> line)
{
    double m = DistanceSq(point, Segment<T>(line.Vertices()[0], line.Vertices()[1]));
    Vector2D<T> prev = line.Vertices()[1];
    double prevX = abs(prev.X()-point.X());
    double prevY = abs(prev.Y()-point.Y());
    double currX, currY;
    for(int i=1;i<line.Vertices().size()-1;i++)
    {
        currX = abs(line.Vertices()[i].X()-point.X());
        currY = abs(line.Vertices()[i].Y()-point.Y());
        if((prevX <= m && currX <= m && (prevX*currX)>0) && (prevY <= m && currY <= m && (prevY*currY)>0))
        {
            m = DistanceSq(point, Segment<T>(line.Vertices()[i], line.Vertices()[i+1]));
        }
        prevX = currX;
        prevY = currY;
    }
    return m;
}

template<class T>
double DistanceSq(Polyline2D<T> line, Vector2D<T> point)
{
    return DistanceSq(point,line);
}
/**
* Computes Point to Polyline Distance
* @param point
* @param line
**/
template<class T>
double Distance(Vector2D<T> point, Polyline2D<T> line)
{
    double m = Distance(point, Segment<T>(line.Vertices()[0], line.Vertices()[1]));
    Vector2D<T> prev = line.Vertices()[1];
    double prevX = std::abs(prev.X()-point.X());
    double prevY = std::abs(prev.Y()-point.Y());
    double currX, currY;
    for(int i=1;i<line.Vertices().size()-1;i++)
    {
        currX = std::abs(line.Vertices()[i].X()-point.X());
        currY = std::abs(line.Vertices()[i].Y()-point.Y());
        if((prevX <= m && currX <= m && (prevX*currX)>0) && (prevY <= m && currY <= m && (prevY*currY)>0))
        {
            m = Distance(point, Segment<T>(line.Vertices()[i], line.Vertices()[i+1]));
        }
        prevX = currX;
        prevY = currY;
    }
    return m;
}

template<class T>
double Distance(Polyline2D<T> line, Vector2D<T> point)
{
    return Distance(point,line);
}

/**
* Computes Line to Line Distance Squared
* @param line1
* @param line2
**/
template<class T>
double DistanceSq(Line<T> line1, Line<T> line2)
{
    Vector2D<T> d2P = line2.D().Perp2();
    if(line1.D()*d2P!=0)
        return 0.0;
    Vector2D<T> d1P = line1.D().Perp2();
    double a = d1P*(line2.P()-line1.P());
    return (a*a)/line1.D().LengthSq();
}

/**
* Computes Line to Line Distance
* @param line1
* @param line2
**/
template<class T>
double Distance(Line<T> line1, Line<T> line2)
{
    Vector2D<T> d2P = line2.D().Perp2();
    if(line1.D()*d2P!=0)
        return 0.0;
    Vector2D<T> d1P = line1.D().Perp2();
    double a = std::abs(d1P*(line2.P()-line1.P()));
    return a/line1.D().Length();
}



/**
* Computes Line to Ray Distance Squared
* @param line
* @param ray
**/
template<class T>
double DistanceSq(Line<T> line, Ray<T> ray)
{
    Vector2D<T> n0 = line.n();
    double c0 = -line.c();
    if((n0*ray.D())*(n0*ray.P()-c0)<0)
        return 0.0;
    double a = n0*ray.P()-c0;
    return ((a*a)/n0.LengthSq());
}

template<class T>
double DistanceSq(Ray<T> ray, Line<T> line)
{
    return DistanceSq(line,ray);
}


/**
* Computes Line to Ray Distance
* @param line
* @param ray
**/
template<class T>
double Distance(Line<T> line, Ray<T> ray)
{
    Vector2D<T> n0 = line.n();
    double c0 = -line.c();
    if((n0*ray.D())*(n0*ray.P()-c0)<0)
        return 0.0;
    return (std::abs(n0*ray.P()-c0)/n0.Length());
}

template<class T>
double Distance(Ray<T> ray, Line<T> line)
{
    return Distance(line,ray);
}


/**
* Computes Line to Segment Distance Squared
* @param line
* @param seg
**/
template<class T>
double DistanceSq(Line<T> line, Segment<T> seg)
{
    Vector2D<T> Q0 = seg.P();
    Vector2D<T> Q1 = seg.P1();
    double c = -line.c();
    Vector2D<T> n = line.n();
    double a = (n*Q0-c);
    double b = (n*Q1-c);
    if(a*b<0)
        return 0.0;
    a = a*a;
    a /= n.LengthSq();
    b = b*b;
    b /= n.LengthSq();
    return minimum(a,b);
}

template<class T>
double DistanceSq(Segment<T> seg, Line<T> line)
{
    return DistanceSq(line,seg);
}


/**
* Computes Line to Segment Distance
* @param line
* @param seg
**/
template<class T>
double Distance(Line<T> line, Segment<T> seg)
{
    Vector2D<T> Q0 = seg.P();
    Vector2D<T> Q1 = seg.P1();
    double c = -line.c();
    Vector2D<T> n = line.n();
    double a = (n*Q0-c);
    double b = (n*Q1-c);
    if(a*b<0)
        return 0.0;
    a /= n.Length();
    b /= n.Length();
    return minimum(std::abs(a),std::abs(b));
}

template<class T>
double Distance(Segment<T> seg, Line<T> line)
{
    return Distance(line,seg);
}

}

#endif

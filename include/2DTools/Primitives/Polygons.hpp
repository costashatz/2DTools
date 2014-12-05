#ifndef POLYGONS_HPP
#define POLYGONS_HPP

/**
* Includes
**/
#include <2DTools/Primitives/LinearShapes.hpp>
#include <vector>
using std::vector;

namespace Tools2D {

/**
* Polyline2D Class
* Polyline is a collection of arbitrary segments (or points)
* I use the form of collection of points..Edges are assumed to be P0->P1->P2->...->Pn
**/
template<class T>
class Polyline2D
{
protected:
    // Collection of points (called vertices)
    vector<Vector2D<T> > vertices;
public:
    /**
    * Default Constructor
    * Initialization
    **/
    Polyline2D()
    {
        vertices = vector<Vector2D<T> >();
    }

    /**
    * Add new point to the polyline
    * virtual method - can be overwritten by subclasses
    * @param point - point to be added
    **/
    virtual void AddPoint(const Vector2D<T>& point)
    {
        vertices.push_back(point);
    }

    /**
    * Get Vertices/Points
    * @return vector<Vector2D> - the collection of points/vertices
    **/
    vector<Vector2D<T> > Vertices() {return vertices;}
};

/**
* Polygon2D Class
* Polygon is a closed Polyline (closed means the first and the last points are the same)
* Assumes there is an extra point in the end identical to the first one
**/
template<class T>
class Polygon2D: public Polyline2D<T>
{
public:
    /**
    * Default Constructor
    * Initialization
    **/
    Polygon2D():Polyline2D<T>(){}

    /**
    * Get the area under the polygon
    * gives correct answer if polygon is simple/convex (=non-adjacent segments do not intersect)
    * @return double - the area
    **/
    virtual double Area()
    {
        double sum = 0.0;
        for(int i=0;i<this->vertices.size();i++)
        {
            unsigned int i_p = (i+1)%this->vertices.size();
            sum += this->vertices[i].X()*this->vertices[i_p].Y()-this->vertices[i].Y()*this->vertices[i_p].X();
        }
        sum /= 2.0;
        return std::abs(sum);
    }

    /**
    * Check if vertices/points are clockwise ordered or not
    * @return bool - a boolean indicating if points are clockwise ordered
    **/
    bool ClockwiseOrdered()
    {
        //clockwise (sum<0)
        double sum = 0.0;
        for(int i=0;i<this->vertices.size();i++)
        {
            unsigned int i_p = (i+1)%this->vertices.size();
            sum += this->vertices[i].X()*this->vertices[i_p].Y()-this->vertices[i].Y()*this->vertices[i_p].X();
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
        for(int i=1;i<this->vertices.size();i++)
        {
            int i_p = (i+1)%this->vertices.size();
            if(((this->vertices[i].X()-this->vertices[i-1].X())*(this->vertices[i_p].Y()-this->vertices[i].Y())-(this->vertices[i].Y()-this->vertices[i-1].Y())*(this->vertices[i_p].X()-this->vertices[i].X()))<0)
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
template<class T>
class Triangle2D: public Polygon2D<T>
{
public:
    /**
    * Constructor
    * @param p0 - the first point of the triangle
    * @param p1 - the second point of the triangle
    * @param p2 - the third point of the triangle
    **/
    Triangle2D(const Vector2D<T>& p0, const Vector2D<T>& p1, const Vector2D<T>& p2):Polygon2D<T>()
    {
        Polygon2D<T>::AddPoint(p0);
        Polygon2D<T>::AddPoint(p1);
        Polygon2D<T>::AddPoint(p2);
    }

    /**
    * Overwrite virtual method AddPoint so that it does nothing
    * We do not want other points to be added in a triangle
    **/
    void AddPoint(const Vector2D<T>& point)
    {
        return;
    }
};

/**
* Rectangle2D Class
**/
template<class T>
class Rectangle2D: public Polygon2D<T>
{
public:
    /**
    * Constructor
    * @param p0 - lower left point of rectangle
    * @param e0 - direction (with length) of horizontal edge
    * @param e1 - direction (with length) of vertical edge
    **/
    Rectangle2D(const Vector2D<T>& p0, const Vector2D<T>& e0, const Vector2D<T>& e1):Polygon2D<T>()
    {
        if((e0*e1)!=0)
            e1 = e0.Perp();
        Polygon2D<T>::AddPoint(p0);
        Polygon2D<T>::AddPoint(p0+e0);
        Polygon2D<T>::AddPoint(p0+e0+e1);
        Polygon2D<T>::AddPoint(p0+e1);
    }

    /**
    * Constructor
    * creates axis aligned rectangle
    * @param p - center of the rectangle
    * @param a - length of horizontal edge
    * @param b - length of vertical edge
    **/
    Rectangle2D(const Vector2D<T>& p, const T& a, const T& b)
    {
        Vector2D<T> p0 = Vector2D<T>(p.X()-a/2.0, p.Y()-b/2.0);
        Polygon2D<T>::AddPoint(p0);
        Vector2D<T> p1 = Vector2D<T>(p.X()+a/2.0, p.Y()-b/2.0);
        Polygon2D<T>::AddPoint(p1);
        Vector2D<T> p2 = Vector2D<T>(p.X()+a/2.0, p.Y()+b/2.0);
        Polygon2D<T>::AddPoint(p2);
        Vector2D<T> p3 = Vector2D<T>(p.X()-a/2.0, p.Y()+b/2.0);
        Polygon2D<T>::AddPoint(p3);
    }

    /**
    * Overwrite virtual method AddPoint so that it does nothing
    * We do not want other points to be added in a triangle
    **/
    void AddPoint(const Vector2D<T>& point)
    {
        return;
    }
};

typedef Polyline2D<double> Polyline2Dd;
typedef Polyline2D<float> Polyline2Df;
typedef Polygon2D<double> Polygon2Dd;
typedef Polygon2D<float> Polygon2Df;
typedef Triangle2D<double> Triangle2Dd;
typedef Triangle2D<float> Triangle2Df;
typedef Rectangle2D<double> Rectangle2Dd;
typedef Rectangle2D<float> Rectangle2Df;

}

#endif

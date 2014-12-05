#ifndef LINEAR_SHAPES_HPP
#define LINEAR_SHAPES_HPP

/**
* Includes
**/
#include <2DTools/Vector2D.hpp>

namespace Tools2D {

/**
* Base Class for Linear Shapes
* I have used the parametric form of linear shape: X(t) = P+t*d, P=point, d=direction vector, t=parameter
* I have also provided methods to "convert" to implicit form (a*x+b*y+c=0)
* Conversion equations (from parametric to implicit): a=-d.Y(), b=d.X(), c=P.X()*d.Y()-P.Y()*d.X()
* Conversion equations (from implicit to parametric): d=(-b,a), p=(1/(a^2+b^2))(-a*c,-b*c), a*P.X()+b*P.Y()=c
**/
template<class T>
class LinearShape
{
protected:
    // LinearShape data
    Vector2D<T> p;
    Vector2D<T> d;
public:
    /**
    * Default Constructor
    * Initializes both p and d to zero vectors
    **/
    LinearShape():p(Vector2D<T>()),d(Vector2D<T>()){}

    /**
    * Constructor - Parametric Form
    * @param P - point P
    * @param D - direction vector d
    **/
    LinearShape(const Vector2D<T>& P, const Vector2D<T>& D):p(P),d(D){}

    /**
    * Copy Constructor
    * @param other - LinearShape to copy from
    **/
    LinearShape(const LinearShape& other)
    {
        this->p = Vector2D<T>(other.p);
        this->d = Vector2D<T>(other.d);
    }

    /**
    * Get Point P - Parametric Form
    * @return Vector2D - the Point p
    **/
    Vector2D<T> P()const {return p;}

    /**
    * Get Direction Vector d - Parametric Form
    * @return Vector2D - the direction vector
    **/
    Vector2D<T> D()const {return d;}

    /**
    * Get "a" value - Implicit Form
    * @return T - the "a" value
    **/
    T a() {return -d.Y();}

    /**
    * Get "b" value - Implicit Form
    * @return T - the "b" value
    **/
    T b() {return d.X();}

    /**
    * Get "c" value - Implicit Form
    * @return T - the "c" value
    **/
    T c() {return (p.X()*d.Y()-p.Y()*d.X());}

    /**
    * Get Normal of Line
    * @return Vector2D - the Normal vector
    **/
    Vector2D<T> n() {return Vector2D<T>(a(),b());}
};

/**
* Line Class
* A line is a linear shape with no restrictions on "t" value of the parametric form
**/
template<class T>
class Line: public LinearShape<T>
{
public:
    /**
    * Default Constructor
    **/
    Line():LinearShape<T>(){}

    /**
    * Constructor - Parametric Form
    * @param P - point P
    * @param D - direction vector d
    **/
    Line(const Vector2D<T>& P, const Vector2D<T>& D):LinearShape<T>(P,D){}

    /**
    * Constructor - Implicit Form
    * @param a - "a" value
    * @param b - "b" value
    * @param c - "c" value
    **/
    Line(const T& a, const T& b, const T& c):LinearShape<T>()
    {
        this->d = Vector2D<T>(-b,a);
        this->p = Vector2D<T>(-a*c,-b*c);
        this->p /= (a*a+b*b);
    }

    /**
    * Constructor - Via Normal Vector
    * @param n - Normal Vector
    * @param d - "d" value
    **/
    Line(const Vector2D<T>& n, const T& d)
    {
        Line(n.X(),n.Y(),-d);
    }
};


/**
* Ray Class
* A ray is a linear shape with t>=0 (parametric form)
**/
template<class T>
class Ray: public LinearShape<T>
{
public:
    /**
    * Default Constructor
    **/
    Ray():LinearShape<T>(){}

    /**
    * Constructor - A ray is defined by a starting point P and a direction D
    * @param P - point P
    * @param D - direction vector d
    **/
    Ray(const Vector2D<T>& P, const Vector2D<T>& D):LinearShape<T>(P,D){}
};


/**
* Segment Class
* A segment is a linear shape with tE[0,1] (parametric form)
**/
template<class T>
class Segment: public LinearShape<T>
{
public:
    /**
    * Default Constructor
    **/
    Segment():LinearShape<T>(){}

    /**
    * Constructor - A segment is defined by two points (P0-starting point, P1-ending point)
    * @param P0 - starting point
    * @param P1 - ending point
    **/
    Segment(const Vector2D<T>& P0, const Vector2D<T>& P1):LinearShape<T>(P0, P1-P0){}


    /**
    * Get Starting Point P0 - Is exactly the same as P() - I've included it for clarity/completeness
    * @return Vector2D - the Starting Point P0
    **/
    Vector2D<T> P0()const {return this->p;}


    /**
    * Get Ending Point P1
    * @return Vector2D - the Ending Point P1
    **/
    Vector2D<T> P1()const {return this->p+this->d;}

    /**
    * Get Length of Segment
    * @return T - length of segment
    **/
    T Length()const { return this->d.Length();}

    /**
    * Get Length Squared of Segment
    * @return T - length squared of segment
    **/
    T LengthSq()const { return this->d.LengthSq();}
};

typedef LinearShape<double> LinearShaped;
typedef LinearShape<float> LinearShapef;
typedef Line<double> Lined;
typedef Line<float> Linef;
typedef Ray<double> Rayd;
typedef Ray<float> Rayf;
typedef Segment<double> Segmentd;
typedef Segment<float> Segmentf;

}

#endif

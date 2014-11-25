#ifndef VECTOR_2D_HPP
#define VECTOR_2D_HPP

/**
* Includes and Required Matrix2D class
**/
#include <cmath>
#include <limits>

namespace Tools2D {

template<class T>
class Matrix2D;


/**
* Simple 2D Vector Class
**/
template<class T>
class Vector2D
{
private:
    T x; // x component
    T y; // y component
public:
    /**
    * Default Constructor
    * Initializes both x and y to zero
    **/
    Vector2D():x(0.0),y(0.0){}

    /**
    * Constructor
    * @param a - value to be assigned to x
    * @param b - value to be assigned to y
    **/
    Vector2D(T a, T b):x(a),y(b){}

    /**
    * Copy Constructor
    * @param other - Vector2D to copy from
    **/
    Vector2D(const Vector2D& other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    /**
    * Get X component
    * @return T - the X value
    **/
    T X() {return x;}

    /**
    * Get Y component
    * @return T - the Y value
    **/
    T Y() {return y;}

    /**
    * Set X component
    * @param a - value to set
    **/
    void SetX(T a) {x=a;}

    /**
    * Set Y component
    * @param b - value to set
    **/
    void SetY(T b) {y=b;}

    /**
    * Make vector zero (x=y=0)
    **/
    void Zero() {x=0.0;y=0.0;}

    /**
    * Test if vector is zero?
    * @return bool - true if vector is zero
    **/
    bool IsZero()const {return (x*x+y*y)<std::numeric_limits<T>::epsilon();}

    /**
    * Normalize vector
    **/
    void Normalize()
    {
        T length = Length();
        // Only normalize if length not zero
        if(length > std::numeric_limits<T>::epsilon())
        {
            x /= length;
            y /= length;
        }
    }

    /**
    * Get Perpendicular Vector (-y,x)
    * @return Vector2D - the perpendicular vector (-y,x)
    * @see Perp2()
    **/
    Vector2D Perp() {return Vector2D(-y,x);}

    /**
    * Get Perpendicular Vector (y,-x)
    * @return Vector2D - the perpendicular vector (y,-x)
    *  @see Perp()
    **/
    Vector2D Perp2() {return Vector2D(y,-x);}

    /**
    * Get Reverse Vector (-x,-y)
    * @return Vector2D - the reversed vector
    **/
    Vector2D Reverse(){return Vector2D(-x,-y);}

    /**
    * Get Length of Vector
    * @return T - length of the vector
    *  @see LengthSq()
    **/
    T Length()const {return sqrt(x*x+y*y);}

    /**
    * Get Length Squared of Vector (avoids sqrt function - for quick tests or fast code)
    * @return T - length squared of the vector
    *  @see Length()
    **/
    T LengthSq()const {return (x*x+y*y);}

    /**
    * Dot product with other vector
    * @param other - vector to compute dot with
    * @return - the dot product
    **/
    T Dot(const Vector2D& other)const
    {
        return (x*other.x+y*other.y);
    }

    /**
    * Distance to other vector
    * @param other - vector to compute distance to
    * @return T - distance to other vector
    *  @see DistanceSq()
    **/
    T Distance(const Vector2D& other)const
    {
        T xSep = other.x-x;
        T ySep = other.y-y;
        return sqrt(xSep*xSep+ySep*ySep);
    }

    /**
    * Distance Squared to other vector (avoids sqrt function - for quick tests or fast code)
    * @param other - vector to compute distance to
    * @return T - distance squared to other vector
    * @see Distance()
    **/
    T DistanceSq(const Vector2D& other)const
    {
        T xSep = other.x-x;
        T ySep = other.y-y;
        return xSep*xSep+ySep*ySep;
    }

    /**
    * Angle with other vector
    * @param other - vector to compute angle with
    * @return T - the angle with the vector
    **/
    T Angle(const Vector2D& other)const
    {
        T dot = Dot(other);
        return acos(dot/(Length()*other.Length()));
    }


    /**
    * Overload basic operators
    * mathematic operators (*,/,+,-)
    * equality operators (==,!=)
    **/
    const Vector2D& operator-=(const Vector2D& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    const Vector2D& operator+=(const Vector2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    const Vector2D& operator*=(const double& other)
    {
        x *= other;
        y *= other;
        return *this;
    }

    // Used for Matrix-Vector multiplications
    inline const Vector2D& operator*=(const Matrix2D<T>& other);

    const Vector2D& operator/=(const double& other)
    {
        // Divide only if other is not zero
        if(other > std::numeric_limits<double>::epsilon())
        {
            x /= other;
            y /= other;
        }
        return *this;
    }

    bool operator==(const Vector2D& other)const
    {
        return (x==other.x)&&(y==other.y);
    }
    bool operator!=(const Vector2D& other)const
    {
        return(x!=other.x)||(y!=other.y);
    }
};

/**
* Functions Overloading basic operators
* mathematic operators
* equality operators
* dot products
**/

template<class T>
T operator*(const Vector2D<T>& vec1, const Vector2D<T>& vec2)
{
    Vector2D<T> res = vec1;
    return res.Dot(vec2);
}

template<class T>
Vector2D<T> operator*(const Vector2D<T>& vec, T val)
{
    Vector2D<T> res = vec;
    res *= val;
    return res;
}

template<class T>
Vector2D<T> operator*(T val, const Vector2D<T>& vec)
{
    Vector2D<T> res = vec;
    res *= val;
    return res;
}

template<class T>
Vector2D<T> operator+(const Vector2D<T>& vec1, const Vector2D<T>& vec2)
{
    Vector2D<T> res = vec1;
    res += vec2;
    return res;
}

template<class T>
Vector2D<T> operator-(const Vector2D<T>& vec1, const Vector2D<T>& vec2)
{
    Vector2D<T> res = vec1;
    res -= vec2;
    return res;
}

template<class T>
Vector2D<T> operator/(const Vector2D<T>& vec, T val)
{
    Vector2D<T> res = vec;
    res /= val;
    return res;
}

typedef Vector2D<double> Vector2Dd;
typedef Vector2D<float> Vector2Df;

}

#endif

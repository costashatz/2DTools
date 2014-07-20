#ifndef VECTOR_2D_H
#define VECTOR_2D_H

/**
* Includes and Required Matrix2D class
**/
#include <cmath>
#include <limits>
#include "helper.h"
class Matrix2D;


/**
* Simple 2D Vector Class
**/
class Vector2D
{
private:
	// Vector Data
	double x;
	double y;
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
	Vector2D(double a, double b):x(a),y(b){}

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
	* @return double - the X value
	**/
	double X() {return x;}

	/**
	* Get Y component
	* @return double - the Y value
	**/
	double Y() {return y;}

	/**
	* Set X component
	* @param a - value to set
	**/
	void setX(double a) {x=a;}

	/**
	* Set Y component
	* @param b - value to set
	**/
	void setY(double b) {y=b;}

	/**
	* Make vector zero (x=y=0)
	**/
	void Zero() {x=0.0;y=0.0;}

	/**
	* Test if vector is zero?
	* @return bool - true if vector is zero
	**/
	bool isZero()const {return (x*x+y*y)<MinDouble;}

	/**
	* Normalize vector
	**/
	void Normalize()
	{
		double length = Length();
		// Only normalize if length not zero
		if(length > numeric_limits<double>::epsilon())
		{
			x /= length;
			y /= length;
		}
	}

	/**
	* Get Perpendicular Vector (-y,x)
	* @return Vector2D - the perpendicular vector (-y,x)
	**/
	Vector2D Perp() {return Vector2D(-y,x);}

	/**
	* Get Perpendicular Vector (y,-x)
	* @return Vector2D - the perpendicular vector (y,-x)
	**/
	Vector2D Perp2() {return Vector2D(y,-x);}

	/**
	* Get Reverse Vector (-x,-y)
	* @return Vector2D - the reversed vector
	**/
	Vector2D Reverse(){return Vector2D(-x,-y);}

	/**
	* Get Length of Vector
	* @return double - length of the vector
	**/
	double Length()const {return sqrt(x*x+y*y);}

	/**
	* Get Length Squared of Vector (avoids sqrt function - for quick tests or fast code)
	* @return double - length squared of the vector
	**/
	double LengthSq()const {return (x*x+y*y);}

	/**
	* Dot product with other vector
	* @param other - vector to compute dot with
	* @return double - the dot product
	**/
	double Dot(const Vector2D& other)const
	{
		return (x*other.x+y*other.y);
	}

	/**
	* Distance to other vector
	* @param other - vector to compute distance to
	* @return double - distance to other vector
	**/
	double Distance(const Vector2D& other)const
	{
		double xSep = other.x-x;
		double ySep = other.y-y;
		return sqrt(xSep*xSep+ySep*ySep);
	}

	/**
	* Distance Squared to other vector (avoids sqrt function - for quick tests or fast code)
	* @param other - vector to compute distance to
	* @return double - distance squared to other vector
	**/
	double DistanceSq(const Vector2D& other)const
	{
		double xSep = other.x-x;
		double ySep = other.y-y;
		return xSep*xSep+ySep*ySep;
	}

	/**
	* Angle with other vector
	* @param other - vector to compute angle with
	* @return double - the angle with the vector
	**/
	double Angle(const Vector2D& other)const
	{
		double dot = Dot(other);
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
	inline const Vector2D& operator*=(const Matrix2D& other);

	const Vector2D& operator/=(const double& other)
	{
		// Divide only if other is not zero
		if(other > numeric_limits<double>::epsilon())
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

double operator*(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D res = vec1;
	return res.Dot(vec2);
}

Vector2D operator*(const Vector2D& vec, double val)
{
	Vector2D res = vec;
	res *= val;
	return res;
}

Vector2D operator*(double val, const Vector2D& vec)
{
	Vector2D res = vec;
	res *= val;
	return res;
}

Vector2D operator+(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D res = vec1;
	res += vec2;
	return res;
}

Vector2D operator-(const Vector2D& vec1, const Vector2D& vec2)
{
	Vector2D res = vec1;
	res -= vec2;
	return res;
}

Vector2D operator/(const Vector2D& vec, double val)
{
	Vector2D res = vec;
	res /= val;
	return res;
}

#endif
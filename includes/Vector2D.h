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
*
**/
class Vector2D
{
private:
	// Vector Data, x and y
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
	* @param b - value to be assigned to x
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

	// Getters
	double X() {return x;}
	double Y() {return y;}

	// Setters
	void setX(double a) {x=a;}
	void setY(double b) {y=b;}

	// Make Vector Zero and test if Zero
	void Zero() {x=0.0;y=0.0;}
	bool isZero()const {return (x*x+y*y)<MinDouble;}

	// Normalization method
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

	// Get Perpedicular or Reverse Vectors
	Vector2D Perp() {return Vector2D(-y,x);}
	Vector2D Perp2() {return Vector2D(y,-x);}
	Vector2D Reverse(){return Vector2D(-x,-y);}

	// Length and LengthSquared (avoids sqrt which is costly - used when precision doesn't matter) methods
	double Length()const {return sqrt(x*x+y*y);}
	double LengthSq()const {return (x*x+y*y);}

	// Dot Product
	double Dot(const Vector2D& other)const
	{
		return (x*other.x+y*other.y);
	}

	// Distance and DistanceSquared between Vectors
	double Distance(const Vector2D& other)const
	{
		double xSep = other.x-x;
		double ySep = other.y-y;
		return sqrt(xSep*xSep+ySep*ySep);
	}
	double DistanceSq(const Vector2D& other)const
	{
		double xSep = other.x-x;
		double ySep = other.y-y;
		return xSep*xSep+ySep*ySep;
	}

	// Angle between Vectors
	double Angle(const Vector2D& other)const
	{
		double dot = Dot(other);
		return acos(dot/(Length()*other.Length()));
	}


	/**
	* Overload basic operators
	* mathematic operators
	* equality operators
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
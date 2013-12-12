#ifndef VECTOR_2D_H
#define VECTOR_2D_H
#include <cmath>
#include <limits>
#include "helper.h"

class Matrix2D;

class Vector2D
{
private:
	double x;
	double y;
public:
	Vector2D():x(0.0),y(0.0){}
	Vector2D(double a, double b):x(a),y(b){}
	Vector2D(const Vector2D& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	double X() {return x;}
	double Y() {return y;}

	void setX(double a) {x=a;}
	void setY(double b) {y=b;}

	void Zero() {x=0.0;y=0.0;}
	bool isZero()const {return (x*x+y*y)<MinDouble;}

	void Normalize()
	{
		double length = Length();
		if(length > numeric_limits<double>::epsilon())
		{
			x /= length;
			y /= length;
		}
	}
	Vector2D Perp() {return Vector2D(-y,x);}
	Vector2D Perp2() {return Vector2D(y,-x);}
	Vector2D Reverse(){return Vector2D(-x,-y);}
	double Length()const {return sqrt(x*x+y*y);}
	double LengthSq()const {return (x*x+y*y);}
	double Dot(const Vector2D& other)const
	{
		return (x*other.x+y*other.y);
	}
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
	double Angle(const Vector2D& other)const
	{
		double dot = Dot(other);
		return acos(dot/(Length()*other.Length()));
	}


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

	inline const Vector2D& operator*=(const Matrix2D& other);

	const Vector2D& operator/=(const double& other)
	{
		x /= other;
		y /= other;
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
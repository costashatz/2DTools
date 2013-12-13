#ifndef MATRIX_2D_H
#define MATRIX_2D_H

/**
* Includes
**/
#include <cstring>
#include "Vector2D.h"

/**
* Simple 2D Matrix Class (3x3 Matrix)
**/
class Matrix2D
{
protected:
	//Matrix Data
	double data[3][3];
public:
	/**
	* Default Constructor
	* Initializes matrix to Identity
	**/
	Matrix2D(){ Identity();}

	/**
	* Copy Constructor
	* @param other - Matrix2D to copy from
	**/
	Matrix2D(const Matrix2D& other)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				data[i][j] = other.data[i][j];
	}

	/**
	* Constructor
	* @param table - 2-dimensional table to copy data from
	**/
	Matrix2D(double** table)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				data[i][j] = table[i][j];
	}

	/**
	* Make matrix Identity
	**/
	void Identity()
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(i==j)
					data[i][j] = 1;
				else
					data[i][j] = 0;
			}
		}
	}

	/**
	* Get Matrix Data
	* @return double** - the data
	**/
	double** getData()
	{
		double** data;
		data = new double*[3];
		for(int i=0;i<3;i++)
		{
			data[i] = new double[3];
			memcpy(data[i],this->data[i],3*sizeof(double));
		}
		return data;
	}

	/**
	* Translate this Matrix
	* @param dx - translation offset in x-axis
	* @param dy - translation offset in y-axis
	**/
	void Translate(double dx, double dy)
	{
		Matrix2D temp = Matrix2D();
		temp.data[2][0] = dx;
		temp.data[2][1] = dy;
		(*this)*=temp;
	}

	/**
	* Scale this Matrix
	* @param dx - scale offset in x-axis
	* @param dy - scale offset in y-axis
	**/
	void Scale(double dx, double dy)
	{
		Matrix2D temp = Matrix2D();
		temp.data[0][0] = dx;
		temp.data[1][1] = dy;
		(*this)*=temp;
	}

	/**
	* Rotate this Matrix (xy-Cartesian plane counter-clockwise through an angle "angle" about the origin)
	* @param angle - angle in radians
	**/
	void Rotate(double angle)
	{
		double c = cos(angle);
		double s = sin(angle);
		Matrix2D temp = Matrix2D();
		temp.data[0][0] = c;
		temp.data[0][1] = s;
		temp.data[1][0] = -s;
		temp.data[1][1] = c;
		(*this)*=temp;
	}

	/**
	* Rotate this Matrix (xy-Cartesian plane counter-clockwise through an angle "angle" about the origin)
	* @param angle - angle in degrees
	**/
	void RotateDegrees(double angle)
	{
		double a = DegreesToRadians(angle);
		Rotate(a);
	}

	/**
	* Rotate this Matrix to align with object that has fwd Forward vector and side Side vector
	* @param fwd - the Forward Vector
	* @param side - the Side Vector
	**/
	void Rotate(Vector2D fwd, Vector2D side)
	{
		Matrix2D temp = Matrix2D();
		temp.data[0][0] = fwd.X();
		temp.data[0][1] = fwd.Y();
		temp.data[1][0] = side.X();
		temp.data[1][1] = side.Y();
		(*this)*=temp;
	}

	/**
	* Get Transpose of the Matrix
	* @return Matrix2D - the transposed matrix
	**/
	Matrix2D Transpose()
	{
		Matrix2D temp = Matrix2D();
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				temp.data[j][i] = data[i][j];
		}
		return temp;
	}

	/**
	* Get the Determinant of the Matrix
	* @return double - the value of the Determinant
	**/
	double Det()const
	{
		return (data[0][0]*data[1][1]*data[2][2]-data[0][0]*data[1][2]*data[2][1]-data[0][1]*data[1][0]*data[2][2]+data[0][1]*data[1][2]*data[0][2]+data[0][2]*data[1][0]*data[2][1]-data[0][2]*data[1][1]*data[2][0]);
	}

	/**
	* Get Inverse of the Matrix
	* @return Matrix2D - the inversed matrix
	**/
	Matrix2D Inverse()
	{
		double det = Det();
		Matrix2D temp = Matrix2D();
		if(det > MinDouble)
		{
			temp.data[0][0] = data[2][2]*data[1][1]-data[2][1]*data[1][2];
			temp.data[0][1] = -(data[2][2]*data[0][2]-data[2][1]*data[0][2]);
			temp.data[0][2] = data[1][2]*data[0][2]-data[1][1]*data[0][2];
			temp.data[1][0] = -(data[2][2]*data[1][0]-data[2][0]*data[1][2]);
			temp.data[1][1] = data[2][2]*data[0][0]-data[2][0]*data[0][2];
			temp.data[1][2] = -(data[1][2]*data[0][0]-data[1][0]*data[0][2]);
			temp.data[2][0] = data[2][1]*data[1][0]-data[2][0]*data[1][1];
			temp.data[2][1] = -(data[2][1]*data[0][0]-data[2][0]*data[0][1]);
			temp.data[2][2] = data[1][1]*data[0][0]-data[1][0]*data[0][1];
			temp /= det;
		}
		return temp;
	}

	/**
	* Overload basic operators
	* mathematic operators (*,/)
	**/
	const Matrix2D& operator*=(const double& other)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				data[i][j] *= other;
		}
		return *this;
	}

	const Matrix2D& operator/=(const double& other)
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				data[i][j] /= other;
		}
		return *this;
	}

	const Matrix2D& operator*=(const Matrix2D& other)
	{
		Matrix2D temp = Matrix2D();
		temp.data[0][0] = data[0][0]*other.data[0][0]+data[0][1]*other.data[1][0]+data[0][2]*other.data[2][0];
		temp.data[0][1] = data[0][0]*other.data[0][1]+data[0][1]*other.data[1][1]+data[0][2]*other.data[2][1];
		temp.data[0][2] = data[0][0]*other.data[0][2]+data[0][1]*other.data[1][2]+data[0][2]*other.data[2][2];

		temp.data[1][0] = data[1][0]*other.data[0][0]+data[1][1]*other.data[1][0]+data[1][2]*other.data[2][0];
		temp.data[1][1] = data[1][0]*other.data[0][1]+data[1][1]*other.data[1][1]+data[1][2]*other.data[2][1];
		temp.data[1][2] = data[1][0]*other.data[0][2]+data[1][1]*other.data[1][2]+data[1][2]*other.data[2][2];

		temp.data[2][0] = data[2][0]*other.data[0][0]+data[2][1]*other.data[1][0]+data[2][2]*other.data[2][0];
		temp.data[2][1] = data[2][0]*other.data[0][1]+data[2][1]*other.data[1][1]+data[2][2]*other.data[2][1];
		temp.data[2][2] = data[2][0]*other.data[0][2]+data[2][1]*other.data[1][2]+data[2][2]*other.data[2][2];
		(*this) = temp;
		return *this;
	}

	friend Vector2D operator*(Vector2D& vec, const Matrix2D& mat);
	friend const Vector2D& Vector2D::operator *=(const Matrix2D& other);
};

/**
* Functions Overloading basic operators
* mathematic operators
* equality operators
* dot products
**/
Matrix2D operator*(const Matrix2D& mat1, double val)
{
	Matrix2D temp = Matrix2D(mat1);
	temp *= val;
	return temp;
}

Matrix2D operator*(double val, const Matrix2D& mat1)
{
	Matrix2D temp = Matrix2D(mat1);
	temp *= val;
	return temp;
}

Matrix2D operator/(const Matrix2D& mat1, double val)
{
	Matrix2D temp = Matrix2D(mat1);
	temp /= val;
	return temp;
}

Matrix2D operator*(const Matrix2D& mat1, const Matrix2D& mat2)
{
	Matrix2D temp = Matrix2D(mat1);
	temp *= mat2;
	return temp;
}

Vector2D operator*(Vector2D& vec, const Matrix2D& mat)
{
	Vector2D temp = Vector2D();
	temp.setX(vec.X()*mat.data[0][0]+vec.Y()*mat.data[1][0]+mat.data[2][0]);
	temp.setY(vec.X()*mat.data[0][1]+vec.Y()*mat.data[1][1]+mat.data[2][1]);
	//vec = temp;
	return temp;
}

Vector2D operator*(const Matrix2D& m, Vector2D& vec)
{
	Vector2D temp = Vector2D(vec);
	temp = temp*m;
	return temp;
}

const Vector2D& Vector2D::operator *=(const Matrix2D& other)
{
	Vector2D temp;
	temp.x = x*other.data[0][0]+y*other.data[1][0]+other.data[2][0];
	temp.y = x*other.data[0][1]+y*other.data[1][1]+other.data[2][1];
	(*this) = temp;
	return *this;
}

#endif
#ifndef MATRIX_2D_H
#define MATRIX_2D_H
#include "Vector2D.h"

class Matrix2D
{
public:
	double data[3][3];
	Matrix2D(){ Identity();}
	Matrix2D(const Matrix2D& other)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				data[i][j] = other.data[i][j];
	}
	Matrix2D(double** table)
	{
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				data[i][j] = table[i][j];
	}

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

	void Translate(double dx, double dy)
	{
		Matrix2D temp = Matrix2D();
		temp.data[2][0] = dx;
		temp.data[2][1] = dy;
		(*this)*=temp;
	}

	void Scale(double dx, double dy)
	{
		Matrix2D temp = Matrix2D();
		temp.data[0][0] = dx;
		temp.data[1][1] = dy;
		(*this)*=temp;
	}

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

	void RotateDegrees(double angle)
	{
		double a = DegreesToRadians(angle);
		Rotate(a);
	}

	void Rotate(Vector2D fwd, Vector2D side)
	{
		Matrix2D temp = Matrix2D();
		temp.data[0][0] = fwd.X();
		temp.data[0][1] = fwd.Y();
		temp.data[1][0] = side.X();
		temp.data[1][1] = side.Y();
		(*this)*=temp;
	}

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

	double Det()const
	{
		return (data[0][0]*data[1][1]*data[2][2]-data[0][0]*data[1][2]*data[2][1]-data[0][1]*data[1][0]*data[2][2]+data[0][1]*data[1][2]*data[0][2]+data[0][2]*data[1][0]*data[2][1]-data[0][2]*data[1][1]*data[2][0]);
	}

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
};

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
	vec = temp;
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
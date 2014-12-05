#ifndef MATRIX_2D_HPP
#define MATRIX_2D_HPP

/**
* Includes
**/
#include <cstring>
#include <2DTools/Math/Vector2D.hpp>

namespace Tools2D {

/**
* Simple 2D Matrix Class (3x3 Matrix)
**/
template<class T>
class Matrix2D
{
protected:
    T data[3][3]; //Matrix Data
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
    Matrix2D(T** table)
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
        memset(data, 0, 9*sizeof(T));
        data[0][0] = data[1][1] = data[2][2] = 1;
    }

    /**
    * Get Matrix Data
    * @return T - the data
    **/
    T** getData()
    {
        T** data;
        data = new T*[3];
        for(int i=0;i<3;i++)
        {
            data[i] = new T[3];
            memcpy(data[i],this->data[i],3*sizeof(T));
        }
        return data;
    }

    /**
    * Translate this Matrix
    * @param dx - translation offset in x-axis
    * @param dy - translation offset in y-axis
    **/
    void Translate(const T& dx, const T& dy)
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
    void Scale(const T& dx, const T& dy)
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
    void Rotate(const T& angle)
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
    void RotateDegrees(const T& angle)
    {
        T a = DegreesToRadians(angle);
        Rotate(a);
    }

    /**
    * Rotate this Matrix to align with object that has fwd Forward vector and side Side vector
    * @param fwd - the Forward Vector
    * @param side - the Side Vector
    **/
    void Rotate(const Vector2D<T>& fwd, const Vector2D<T>& side)
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
    * @return T - the value of the Determinant
    **/
    T Det()const
    {
        return (data[0][0]*data[1][1]*data[2][2]-data[0][0]*data[1][2]*data[2][1]-data[0][1]*data[1][0]*data[2][2]+data[0][1]*data[1][2]*data[0][2]+data[0][2]*data[1][0]*data[2][1]-data[0][2]*data[1][1]*data[2][0]);
    }

    /**
    * Get Inverse of the Matrix
    * @return Matrix2D - the inversed matrix
    **/
    Matrix2D Inverse()
    {
        T det = Det();
        Matrix2D temp = Matrix2D();
        if(det > std::numeric_limits<T>::epsilon())
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
    const Matrix2D& operator*=(const T& other)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
                data[i][j] *= other;
        }
        return *this;
    }

    const Matrix2D& operator/=(const T& other)
    {
        // Divide only if other is not zero
        if(other > std::numeric_limits<T>::epsilon())
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                    data[i][j] /= other;
            }
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

    /**
    * Overloading () operator
    * Access Matrix Matlab-like
    * @params i - row index to return
    * @params j - column index to return
    * @return T - value of i,j-th element
    **/
    T& operator()(unsigned int i, unsigned int j)
    {
        return data[i][j];
    }

    template<class U>
    friend Vector2D<U> operator*(Vector2D<U>& vec, const Matrix2D<U>& mat);
    friend const Vector2D<T>& Vector2D<T>::operator *=(const Matrix2D& other);
};

/**
* Functions Overloading basic operators
* mathematic operators
* equality operators
* dot products
**/

template<class T>
Matrix2D<T> operator*(const Matrix2D<T>& mat1, T val)
{
    Matrix2D<T> temp = Matrix2D<T>(mat1);
    temp *= val;
    return temp;
}

template<class T>
Matrix2D<T> operator*(T val, const Matrix2D<T>& mat1)
{
    Matrix2D<T> temp = Matrix2D<T>(mat1);
    temp *= val;
    return temp;
}

template<class T>
Matrix2D<T> operator/(const Matrix2D<T>& mat1, T val)
{
    Matrix2D<T> temp = Matrix2D<T>(mat1);
    temp /= val;
    return temp;
}

template<class T>
Matrix2D<T> operator*(const Matrix2D<T>& mat1, const Matrix2D<T>& mat2)
{
    Matrix2D<T> temp = Matrix2D<T>(mat1);
    temp *= mat2;
    return temp;
}

template<class T>
Vector2D<T> operator*(Vector2D<T>& vec, const Matrix2D<T>& mat)
{
    Vector2D<T> temp = Vector2D<T>();
    temp.SetX(vec.X()*mat.data[0][0]+vec.Y()*mat.data[1][0]+mat.data[2][0]);
    temp.SetY(vec.X()*mat.data[0][1]+vec.Y()*mat.data[1][1]+mat.data[2][1]);
    return temp;
}

template<class T>
Vector2D<T> operator*(const Matrix2D<T>& m, Vector2D<T>& vec)
{
    Vector2D<T> temp = Vector2D<T>(vec);
    temp = temp*m;
    return temp;
}

template<class T>
const Vector2D<T>& Vector2D<T>::operator *=(const Matrix2D<T>& other)
{
    Vector2D<T> temp;
    temp.x = x*other.data[0][0]+y*other.data[1][0]+other.data[2][0];
    temp.y = x*other.data[0][1]+y*other.data[1][1]+other.data[2][1];
    (*this) = temp;
    return *this;
}

typedef Matrix2D<double> Matrix2d;
typedef Matrix2D<float> Matrix2;

}

#endif

#ifndef MATRIX_1_HPP
#define MATRIX_1D_HPP

/**
* Includes
**/
#include <cstring>
#include <cmath>
#include <2DTools/Math/Vector2D.hpp>

namespace Tools2D {

/**
* Simple 1D Matrix Class (2x2 Matrix)
**/
template<class T>
class Matrix1D
{
protected:
    T data[2][2]; //Matrix Data
public:
    /**
    * Default Constructor
    * Initializes matrix to Identity
    **/
    Matrix1D(){ Identity();}

    /**
    * Copy Constructor
    * @param other - Matrix2D to copy from
    **/
    Matrix1D(const Matrix1D& other)
    {
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                data[i][j] = other.data[i][j];
    }

    /**
    * Constructor
    * @param table - 2-dimensional table to copy data from
    **/
    Matrix1D(T** table)
    {
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                data[i][j] = table[i][j];
    }

    /**
    * Make matrix Identity
    **/
    void Identity()
    {
        memset(data, 0, 4*sizeof(T));
        data[0][0] = data[1][1] = 1;
    }

    /**
    * Get Matrix Data
    * @return T - the data
    **/
    T** getData()
    {
        T** data;
        data = new T*[2];
        for(int i=0;i<2;i++)
        {
            data[i] = new T[2];
            memcpy(data[i],this->data[i],2*sizeof(T));
        }
        return data;
    }

    /**
    * Get Transpose of the Matrix
    * @return Matrix1D - the transposed matrix
    **/
    Matrix1D Transpose()
    {
        Matrix1D temp = Matrix1D();
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
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
        return (data[0][0]*data[1][1]-data[0][1]*data[1][0]);
    }

    /**
    * Get the Trace of the Matrix
    * @return T - the value of the Trace
    **/
    T Trace()const
    {
        return (data[0][0]+data[1][1]);
    }

    /**
    * Get the eigenvalues of the Matrix
    * @return T[2] - array with the eigenvalues
    **/
    T* Eigenvalues()const
    {
        T* eigen = new T[2];
        T t = Trace();
        T d = Det();
        eigen[0] = t/2+sqrt(t*t/4-d);
        eigen[1] = t/2-sqrt(t*t/4-d);
        return eigen;
    }

    /**
    * Get the eigen vectors of the Matrix
    * @return Vector2D[2] - array with the eigen vectors
    **/
    Vector2D<T>* Eigenvectors()const
    {
        Vector2D<T>* eigenV = new Vector2D<T>[2];
        T* eigen = Eigenvalues();

        if(std::abs(data[1][0]) > std::numeric_limits<T>::epsilon())
        {
            eigenV[0] = Vector2D<T>(eigen[0]-data[1][1], data[1][0])/data[1][0];
            eigenV[1] = Vector2D<T>(eigen[1]-data[1][1], data[1][0])/data[1][0];
        }
        else if(std::abs(data[0][1]) > std::numeric_limits<T>::epsilon())
        {
            eigenV[0] = Vector2D<T>(data[0][1], eigen[0]-data[0][0])/data[0][1];
            eigenV[1] = Vector2D<T>(data[0][1], eigen[1]-data[0][0])/data[0][1];
        }
        else
        {
            eigenV[0] = Vector2D<T>(1, 0);
            eigenV[1] = Vector2D<T>(0, 1);
        }
        return eigenV;
    }

    /**
    * Get the eigen values of the Matrix in matrix form
    **/
    void EigenDiagonalize(Matrix1D<T>& D, Matrix1D<T>& Q)const
    {
        T* eigen = Eigenvalues();
        Vector2D<T>* eigenV = Eigenvectors();
        if(eigen[0] > eigen[1])
        {
            T tmp = eigen[0];
            eigen[0] = eigen[1];
            eigen[1] = tmp;
            Vector2D<T> tmpV = eigenV[0];
            eigenV[0] = eigenV[1];
            eigenV[1] = tmpV;
        }
        D.Identity();
        D(0,0) = eigen[0];
        D(1,1) = eigen[1];
        Q.Identity();
        Q(0,0) = eigenV[0].X();
        Q(1,0) = eigenV[0].Y();
        Q(0,1) = eigenV[1].X();
        Q(1,1) = eigenV[1].Y();
    }

    /**
    * Get Inverse of the Matrix
    * @return Matrix1D - the inversed matrix
    **/
    Matrix1D Inverse()
    {
        T det = Det();
        Matrix1D temp = Matrix1D();
        if(std::abs(det) > std::numeric_limits<T>::epsilon())
        {
            temp.data[0][0] = data[1][1];
            temp.data[0][1] = -data[0][1];
            temp.data[1][0] = -data[1][0];
            temp.data[1][1] = data[0][0];
            temp /= det;
        }
        return temp;
    }

    /**
    * Overload basic operators
    * mathematic operators (*,/)
    **/
    const Matrix1D& operator*=(const T& other)
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<2;j++)
                data[i][j] *= other;
        }
        return *this;
    }

    const Matrix1D& operator/=(const T& other)
    {
        // Divide only if other is not zero
        if(std::abs(other) > std::numeric_limits<T>::epsilon())
        {
            for(int i=0;i<2;i++)
            {
                for(int j=0;j<2;j++)
                    data[i][j] /= other;
            }
        }
        return *this;
    }

    const Matrix1D& operator*=(const Matrix1D& other)
    {
        Matrix1D temp = Matrix1D();
        temp.data[0][0] = data[0][0]*other.data[0][0]+data[0][1]*other.data[1][0];
        temp.data[0][1] = data[0][0]*other.data[0][1]+data[0][1]*other.data[1][1];

        temp.data[1][0] = data[1][0]*other.data[0][0]+data[1][1]*other.data[1][0];
        temp.data[1][1] = data[1][0]*other.data[0][1]+data[1][1]*other.data[1][1];
        (*this) = temp;
        return *this;
    }

    const Matrix1D& operator-=(const Matrix1D& other)
    {
        Matrix1D temp = Matrix1D();
        temp.data[0][0] = data[0][0]-other.data[0][0];
        temp.data[0][1] = data[0][1]-other.data[0][1];
        temp.data[1][0] = data[1][0]-other.data[1][0];
        temp.data[1][1] = data[1][1]-other.data[1][1];
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
    friend Vector2D<U> operator*(Vector2D<U>& vec, const Matrix1D<U>& mat);
    friend const Vector2D<T>& Vector2D<T>::operator *=(const Matrix1D& other);
};

/**
* Functions Overloading basic operators
* mathematic operators
* equality operators
* dot products
**/

template<class T>
Matrix1D<T> operator*(const Matrix1D<T>& mat1, T val)
{
    Matrix1D<T> temp = Matrix1D<T>(mat1);
    temp *= val;
    return temp;
}

template<class T>
Matrix1D<T> operator*(T val, const Matrix1D<T>& mat1)
{
    Matrix1D<T> temp = Matrix1D<T>(mat1);
    temp *= val;
    return temp;
}

template<class T>
Matrix1D<T> operator/(const Matrix1D<T>& mat1, T val)
{
    Matrix1D<T> temp = Matrix1D<T>(mat1);
    temp /= val;
    return temp;
}

template<class T>
Matrix1D<T> operator*(const Matrix1D<T>& mat1, const Matrix1D<T>& mat2)
{
    Matrix1D<T> temp = Matrix1D<T>(mat1);
    temp *= mat2;
    return temp;
}

template<class T>
Matrix1D<T> operator-(const Matrix1D<T>& mat1, const Matrix1D<T>& mat2)
{
    Matrix1D<T> temp = Matrix1D<T>(mat1);
    temp -= mat2;
    return temp;
}

template<class T>
Vector2D<T> operator*(Vector2D<T>& vec, const Matrix1D<T>& mat)
{
    Vector2D<T> temp = Vector2D<T>();
    temp.SetX(vec.X()*mat.data[0][0]+vec.Y()*mat.data[1][0]);
    temp.SetY(vec.X()*mat.data[0][1]+vec.Y()*mat.data[1][1]);
    return temp;
}

template<class T>
Vector2D<T> operator*(const Matrix1D<T>& m, Vector2D<T>& vec)
{
    Vector2D<T> temp = Vector2D<T>(vec);
    temp = temp*m;
    return temp;
}

template<class T>
const Vector2D<T>& Vector2D<T>::operator *=(const Matrix1D<T>& other)
{
    Vector2D<T> temp;
    temp.x = x*other.data[0][0]+y*other.data[1][0];
    temp.y = x*other.data[0][1]+y*other.data[1][1];
    (*this) = temp;
    return *this;
}

typedef Matrix1D<double> Matrix1;
typedef Matrix1D<float> Matrix1d;

}

#endif

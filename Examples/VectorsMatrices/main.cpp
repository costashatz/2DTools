#include <iostream>
#include "helper.h"
#include "Matrix2D.h"
#include "Distances2D.h"
using namespace std;

/**
* Simple Example using Vector2D and Matrix2D classes
**/

int main()
{
	//Vector Addition
	Vector2D a = Vector2D(10,7);
	Vector2D b = Vector2D(-2,1);
	Vector2D c = a+b;
	cout<<"("<<a.X()<<" "<<a.Y()<<") + ("<<b.X()<<" "<<b.Y()<<") = ("<<c.X()<<" "<<c.Y()<<")\n";
	//Translation
	Matrix2D mat = Matrix2D();
	mat.Identity();
	mat.Translate(2,3);
	double** data;
	data = mat.getData(); //get the matrix data
	cout<<"Matrix -- Column Major (so far...maybe row major in next push)\n";
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<data[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"--------------------\n";
	c = a*mat;
	cout<<"("<<a.X()<<" "<<a.Y()<<") Traslated by ("<<2<<" "<<3<<") = ("<<c.X()<<" "<<c.Y()<<")\n";
	//Rotation
	a = Vector2D(1,2);
	mat.Identity();
	mat.Rotate(HalfPi);
	c = a*mat;
	cout<<"("<<a.X()<<" "<<a.Y()<<") rotated by pi/2 radians to ("<<c.X()<<" "<<c.Y()<<")\n";
	mat.Identity();
	mat.RotateDegrees(90);
	c = a*mat;
	cout<<"("<<a.X()<<" "<<a.Y()<<") rotated by 90 degrees to ("<<c.X()<<" "<<c.Y()<<")\n";
	return(0);
}

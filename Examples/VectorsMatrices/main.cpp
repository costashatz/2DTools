#include <iostream>
#include <2DTools/Misc/Helper.hpp>
#include <2DTools/Math/Matrix2D.hpp>
#include <2DTools/Math/Vector2D.hpp>
using namespace std;
using namespace Tools2D;

/**
* Simple Example using Vector2D and Matrix2D classes
**/

int main()
{
	//Vector Addition
    Vector2 a = Vector2(10,7);
    Vector2 b = Vector2(-2,1);
    Vector2 c = a+b;
	cout<<"("<<a.X()<<" "<<a.Y()<<") + ("<<b.X()<<" "<<b.Y()<<") = ("<<c.X()<<" "<<c.Y()<<")\n";
	//Translation
    Matrix2 mat = Matrix2();
	mat.Identity();
	mat.Translate(2,3);
	float** data;
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
    a = Vector2(1,2);
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

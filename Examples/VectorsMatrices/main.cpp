#include <iostream>
#include "helper.h"
#include "Matrix2D.h"
#include "Distances2D.h"
using namespace std;

int main()
{
	Vector2D a = Vector2D(10,7);
	Vector2D b = Vector2D(-2,1);
	Vector2D c = a+b;
	cout<<"("<<a.X()<<" "<<a.Y()<<") + ("<<b.X()<<" "<<b.Y()<<") = ("<<c.X()<<" "<<c.Y()<<")\n";
	Matrix2D mat = Matrix2D();
	mat.Identity();
	mat.Translate(2,3);
	cout<<"Matrix -- Column Major (so far...maybe row major in next push)\n";
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<mat.data[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"--------------------\n";
	//c = Vector2D();
	c = a*mat;
	cout<<"("<<a.X()<<" "<<a.Y()<<") Traslated by ("<<2<<" "<<3<<") = ("<<c.X()<<" "<<c.Y()<<")\n";
	return(0);
}

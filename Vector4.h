#pragma once
#include <iostream>
#include "armadillo"

// 4 Dimensional representation of a point in R3. Overloads operators for easy intuitive use.

class Vector4
{
private:
	float coordinates[4];

public:
	Vector4(float x, float y, float z, float w);
	Vector4();
	~Vector4(void);
	
	float operator()(int index);

	friend Vector4 operator/(Vector4& operator1, float divisor);
	friend Vector4 operator+(Vector4& operator1, Vector4& operator2);
	friend Vector4 operator-(Vector4& operator1, Vector4& operator2);
	friend float operator*(Vector4& operator1, Vector4& operator2);	//Dot product
	friend Vector4 operator-(Vector4& operator1);						//Unary minus sign

	//Operators involving a Vector4 and a float

	friend Vector4 operator+(Vector4& operator1, float summer);			//Addition by a float
	friend Vector4 operator+(float summer, Vector4& operator1);
	friend Vector4 operator-(Vector4 operator1, float to_be_subtracted);	//Subtraction by a float
	friend Vector4 operator-(float to_be_subtracted, Vector4& operator1);
	friend Vector4 operator*(Vector4& operator1, float multiplier);		//Scalar multiplication
	friend Vector4 operator*(float multiplier, Vector4& operator1);

	void setCoordinate(int ID, float value);
	float getMagnitude();
	Vector4 transform(arma::fmat transform);
};
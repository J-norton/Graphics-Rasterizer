#pragma once
#include <iostream>

// 3 Dimensional Vector3. Overloads operators for easy intuitive use.


class Vector3
{
private:
	float coordinates[3];

public:
	Vector3(float x, float y, float z);
	Vector3(float* coordinate_values);
	Vector3();
	~Vector3(void);
	
	float operator()(int index);

	friend Vector3 operator/(Vector3& operator1, float divisor);
	friend Vector3 operator+(Vector3& operator1, Vector3& operator2);
	friend Vector3 operator-(Vector3& operator1, Vector3& operator2);
	friend float operator*(Vector3& operator1, Vector3& operator2);	//Dot product
	friend Vector3 operator-(Vector3& operator1);						//Unary minus sign

	//Operators involving a Vector3 and a float

	friend Vector3 operator+(Vector3& operator1, float summer);			//Addition by a float
	friend Vector3 operator+(float summer, Vector3& operator1);
	friend Vector3 operator-(Vector3& operator1, float to_be_subtracted);	//Subtraction by a float
	friend Vector3 operator-(float to_be_subtracted, Vector3& operator1);
	friend Vector3 operator*(Vector3& operator1, float multiplier);		//Scalar multiplication
	friend Vector3 operator*(float multiplier, Vector3& operator1);

	void setCoordinate(int ID, float value);
	float getMagnitude();
};
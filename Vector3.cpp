#include "Vector3.h"


Vector3::Vector3(float* coordinate_values)
{
	for (int i = 0; i < 3; i++)
		*(coordinates + i) = *(coordinate_values + i);
}


//By default Vector3s will be initialized to (0, 0, 0)
Vector3::Vector3()
{
	for (int i = 0; i < 3; i++)
		*(coordinates + i) = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
}


Vector3::~Vector3(void)
{
}


//Uses friend functions for binary + operator
Vector3 operator+ (Vector3& operator1, Vector3& operator2)
{
	return Vector3(operator1(0) + operator2(0), operator1(1) + operator2(1), operator1(2) + operator2(2));
}

//Addition by a float

Vector3 operator+(Vector3& operator1, float to_be_added)
{
	return Vector3(operator1(0) + to_be_added, operator1(1) + to_be_added, operator1(2) + to_be_added);
}

Vector3 operator+(float to_be_added, Vector3& operator1)
{
	return Vector3(operator1(0) + to_be_added, operator1(1) + to_be_added, operator1(2) + to_be_added);
}

//Subtraction by a float

Vector3 operator-(Vector3& operator1, float to_be_subtracted)
{
	return Vector3(operator1(0) - to_be_subtracted, operator1(1) - to_be_subtracted, operator1(2) - to_be_subtracted);
}

Vector3 operator-(float to_subtract_from, Vector3& operator1)
{
	return Vector3(to_subtract_from - operator1(0), to_subtract_from - operator1(1), to_subtract_from - operator1(2));
}

//Unary minus
Vector3 operator-(Vector3& op)
{
	return Vector3(-op(0), -op(1), -op(2));
}



//Scalar multiplication
Vector3 operator*(Vector3& operator1, float multiplier)
{
	return Vector3(operator1(0) * multiplier, operator1(1) * multiplier, operator1(2) * multiplier);
}

Vector3 operator*(float multiplier, Vector3& op)
{
	return Vector3(op(0) * multiplier, op(1) * multiplier, op(2) * multiplier);
}


//Friend non-member function for binary subtraction of Vector3s
Vector3 operator-(Vector3& op1, Vector3& op2)
{
	return Vector3(op1(0) - op2(0), op1(1) - op2(1), op1(2) - op2(2));
}

Vector3 operator/(Vector3& operator1, float divisor)
{
	return Vector3(operator1(0) / divisor, operator1(1) / divisor, operator1(2) / divisor);
}


void Vector3::setCoordinate(int ID, float value)
{
	if (ID >= 3 || ID < 0)
		return;
	else
		*(coordinates + ID) = value;
}


// Use () to access coordinates through their index. By definition x = 0, y = 1, z = 2
float Vector3::operator()(int index)
{
	if (index >= 3 || index < 0)
		return 0;

	return *(coordinates + index);
}

//Compute the dot product of two Vector3s

float operator*(Vector3& operator1, Vector3& operator2)
{
	return operator1(0) * operator2(0) + operator1(1) * operator2(1) + operator1(2) * operator2(2);
}


float Vector3::getMagnitude()
{
	return sqrt(pow(coordinates[0], 2) + pow(coordinates[1], 2) + pow(coordinates[2], 2));
}



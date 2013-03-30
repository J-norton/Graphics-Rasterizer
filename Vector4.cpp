#include "Vector4.h"

//By default Vector4s will be initialized to (0, 0, 0, 0)
Vector4::Vector4()
{
	for (int i = 0; i < 4; i++)
		*(coordinates + i) = 0;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	coordinates[0] = x;
	coordinates[1] = y;
	coordinates[2] = z;
	coordinates[3] = w;
}


Vector4::~Vector4(void)
{
}


//Uses friend functions for binary + operator
Vector4 operator+ (Vector4& operator1, Vector4& operator2)
{
	return Vector4(operator1(0) + operator2(0), operator1(1) + operator2(1), operator1(2) + operator2(2), operator1(3) + operator2(3));
}

//Addition by a float

Vector4 operator+(Vector4& operator1, float to_be_added)
{
	return Vector4(operator1(0) + to_be_added, operator1(1) + to_be_added, operator1(2) + to_be_added, operator1(3) + to_be_added);
}

Vector4 operator+(float to_be_added, Vector4& operator1)
{
	return Vector4(operator1(0) + to_be_added, operator1(1) + to_be_added, operator1(2) + to_be_added, operator1(3) + to_be_added);
}

//Subtraction by a float

Vector4 operator-(Vector4& operator1, float to_be_subtracted)
{
	return Vector4(operator1(0) - to_be_subtracted, operator1(1) - to_be_subtracted, operator1(2) - to_be_subtracted, operator1(3) - to_be_subtracted);
}

Vector4 operator-(float to_subtract_from, Vector4& operator1)
{
	return Vector4(to_subtract_from - operator1(0), to_subtract_from - operator1(1), to_subtract_from - operator1(2), to_subtract_from - operator1(3));
}

//Unary minus
Vector4 operator-(Vector4& op)
{
	return Vector4(-op(0), -op(1), -op(2), -op(3));
}



//Scalar multiplication
Vector4 operator*(Vector4& operator1, float multiplier)
{
	return Vector4(operator1(0) * multiplier, operator1(1) * multiplier, operator1(2) * multiplier, operator1(3) * multiplier);
}

Vector4 operator*(float multiplier, Vector4& op)
{
	return Vector4(op(0) * multiplier, op(1) * multiplier, op(2) * multiplier, op(3) * multiplier);
}


//Friend non-member function for binary subtraction of Vector4s
Vector4 operator-(Vector4& op1, Vector4& op2)
{
	return Vector4(op1(0) - op2(0), op1(1) - op2(1), op1(2) - op2(2), op1(3) - op2(3));
}

Vector4 operator/(Vector4& operator1, float divisor)
{
	return Vector4(operator1(0) / divisor, operator1(1) / divisor, operator1(2) / divisor, operator1(3) / divisor);
}


void Vector4::setCoordinate(int ID, float value)
{
	if (ID >= 4 || ID < 0)
		return;
	else
		*(coordinates + ID) = value;
}


// Use () to access coordinates through their index. By definition x = 0, y = 1, z = 2
float Vector4::operator()(int index)
{
	if (index >= 4 || index < 0)
		return 0;

	return *(coordinates + index);
}

//Compute the dot product of two Vector4s

float operator*(Vector4& operator1, Vector4& operator2)
{
	//return operator1(0) * operator2(0) + operator1(1) * operator2(1) + operator1(2) * operator2(2) + operator1(3) * operator2(3);
	return operator1(0) * operator2(0) + operator1(1) * operator2(1) + operator1(2) * operator2(2);
}


float Vector4::getMagnitude()
{
	return sqrt(pow(coordinates[0], 2) + pow(coordinates[1], 2) + pow(coordinates[2], 2) + pow(coordinates[3], 2));
}


Vector4 Vector4::transform(arma::fmat transformation)
{
	arma::fmat v_mat = arma::fmat(coordinates, 4, 1);
	arma::fmat tmp = transformation * v_mat;
	Vector4 to_return = Vector4(tmp(0), tmp(1), tmp(2), tmp(3));
	//if (abs(to_return(3) - 1.0) < 0.001)
	
	to_return = to_return / to_return(3);

	return to_return;
}
#include "Vertex.h"


Vertex::Vertex(void) :
	x(0.0),
	y(0.0),
	z(0.0)
{
}

Vertex::Vertex(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
}


float Vertex::operator[](int index)
{
	switch (index)
	{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return 0.0;
	}
}


Vertex::~Vertex(void)
{
}

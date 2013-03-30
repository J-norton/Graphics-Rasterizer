#include "Triangle.h"


Triangle::Triangle()
{
	for (int i = 0; i < 3; i++)
		vertices[i] = Vector4();
}


Triangle::~Triangle(void)
{
}

Triangle Triangle::transform(arma::fmat trans_matr)
{
	for (int i = 0; i < 3; i++)
		vertices[i] = vertices[i].transform(trans_matr);

	return *this;
}

void Triangle::setWorldVertices()
{
	for (int i = 0; i < 3; i++)
	{
		world_vertices[i] = vertices[i];
	}
}

Triangle::Triangle(Vector4 v1, Vector4 v2, Vector4 v3)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
}

void Triangle::computeVectors()
{
	Vector4 v1_v0 = vertices[1] - vertices[0];
	Vector4 v2_v0 = vertices[2] - vertices[0];
	
	Vector4 temp = (vertices[0] + vertices[1] + vertices[2] ) / 3.0;

	centroid = Vector3(temp(0), temp(1), temp(2));
	//Want cross(v1 - v0, v2 - v0)
}


void Triangle::setNormal(Vector3 normal, int ID_num)
{
	unit_normal[ID_num] = normal / normal.getMagnitude();

}
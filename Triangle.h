#pragma once

#include "Vector4.h"
#include "Vector3.h"
#include "ImagePlane.h"


class Triangle
{
public:
	void computeVectors();
	Vector4 vertices[3];
	Vector4 world_vertices[3];
	void setWorldVertices();

	Triangle transform(arma::fmat tran_matr);
	Vector3 centroid;
	Vector3 unit_normal[3];
	Triangle(Vector4 v1, Vector4 v2, Vector4 v3);
	Triangle(void);
	~Triangle(void);
	void setNormal(Vector3 normal, int num);
};


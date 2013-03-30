#pragma once
#include "GeometricObj.h"

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include "Vector4.h"

class Sphere : public GeometricObj
{
private:

	int     gNumVertices;		 // Number of 3D vertices.
	int     gNumTriangles;		 // Number of triangles.
	int*    gIndexBuffer;		 // Vertex indices for the triangles.

public:
	Sphere();
	Sphere(int height, int width);
	~Sphere(void);
};





#include "TriangleMesh.h"


TriangleMesh::TriangleMesh()
{
	triangles.push_back(Triangle(Vector4(-1.0, -1.0, -1.0, 1.0), Vector4(-1.0, 1.0, -1.0, 1.0), Vector4(1.0, 1.0, -1.0, 1.0)));

	surface_mat.ambient = RGBColor(0, 1, 0);
	surface_mat.specular = RGBColor(0.5, 0.5, 0.5);
	surface_mat.diffuse = RGBColor(0, 0.5, 0);
	surface_mat.phong_exponent = 32.0;
}


TriangleMesh::~TriangleMesh(void)
{
}

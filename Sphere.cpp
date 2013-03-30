#include "Sphere.h"

Sphere::Sphere() : GeometricObj()
{
}

Sphere::Sphere(int height, int width) : GeometricObj()
{
    float theta, phi;
    int t = 0;
    
    gNumVertices    = (height - 2) * width + 2;
    gNumTriangles   = (height - 2) * (width - 1) * 2;
    
	Vector4* vertices = new Vector4[gNumVertices];

    gIndexBuffer    = new int[3*gNumTriangles];
    
    for (int j = 1; j < height-1; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            theta = (float) j / (height-1) * M_PI;
            phi   = (float) i / (width-1)  * M_PI * 2;
            
            float   x   = sinf(theta) * cosf(phi);
            float   y   = cosf(theta);
            float   z   = -sinf(theta) * sinf(phi);
            
            // TODO: Set vertex t in the vertex array to {x, y, z}.
            
			vertices[t] = Vector4(x, y, z, 1.0);

            t++;
        }
    }
    
    // TODO: Set vertex t in the vertex array to {0, 1, 0}.
    vertices[t] = Vector4(0, 1, 0, 1);
    t++;
    

    // TODO: Set vertex t in the vertex array to {0, -1, 0}.
	vertices[t] = Vector4(0.0, -1.0, 0.0, 1.0);
    t++;
    
    t = 0;
    for (int j = 0; j < height-3; ++j)
    {
        for (int i = 0; i < width-1; ++i)
        {
            gIndexBuffer[t++] = j*width + i;
            gIndexBuffer[t++] = (j+1)*width + (i+1);
            gIndexBuffer[t++] = j*width + (i+1);
            gIndexBuffer[t++] = j*width + i;
            gIndexBuffer[t++] = (j+1)*width + i;
            gIndexBuffer[t++] = (j+1)*width + (i+1);
        }
    }
    for (int i = 0; i < width-1; ++i)
    {
        gIndexBuffer[t++] = (height-2)*width;
        gIndexBuffer[t++] = i;
        gIndexBuffer[t++] = i + 1;
        gIndexBuffer[t++] = (height-2)*width + 1;
        gIndexBuffer[t++] = (height-3)*width + (i+1);
        gIndexBuffer[t++] = (height-3)*width + i;
    }
    
	for (int i = 0; i < gNumTriangles; i++)
	{
		int k0 = gIndexBuffer[3 * i];
		int k1 = gIndexBuffer[3 * i + 1];
		int k2 = gIndexBuffer[3 * i + 2];

		triangles.push_back(Triangle(vertices[k0], vertices[k1], vertices[k2]));
	}

	num_triangles = triangles.size();
	delete[] vertices;
	delete[] gIndexBuffer;


	model_trans(0, 0) = 2.0;
	model_trans(0, 1) = 0.0;
	model_trans(0, 2) = 0.0;
	model_trans(0, 3) = 0.0;

	model_trans(1, 0) = 0.0;
	model_trans(1, 1) = 2.0;
	model_trans(1, 2) = 0.0;
	model_trans(1, 3) = 0.0;

	model_trans(2, 0) = 0.0;
	model_trans(2, 1) = 0.0;
	model_trans(2, 2) = 2.0;
	model_trans(2, 3) = -7.0;

	model_trans(3, 0) = 0.0;
	model_trans(3, 1) = 0.0;
	model_trans(3, 2) = 0.0;
	model_trans(3, 3) = 1.0;

	(*this).transform(model_trans);

	for (int i = 0; i < triangles.size(); i++)
	{
		triangles[i].computeVectors();
		triangles[i].setWorldVertices();

		triangles[i].setNormal(Vector3(triangles[i].vertices[0](0), triangles[i].vertices[0](1), triangles[i].vertices[0](2)) - Vector3(0, 0, -7), 0);
		triangles[i].setNormal(Vector3(triangles[i].vertices[1](0), triangles[i].vertices[1](1), triangles[i].vertices[1](2)) - Vector3(0, 0, -7), 1);
		triangles[i].setNormal(Vector3(triangles[i].vertices[2](0), triangles[i].vertices[2](1), triangles[i].vertices[2](2)) - Vector3(0, 0, -7), 2);

	}

	//Should probably be implemented somewhere else. But I digress...
	surface_mat.ambient = RGBColor(0, 1, 0);
	surface_mat.specular = RGBColor(0.5, 0.5, 0.5);
	surface_mat.diffuse = RGBColor(0, 0.5, 0);
	surface_mat.phong_exponent = 32.0;

}

Sphere::~Sphere(void)
{
}

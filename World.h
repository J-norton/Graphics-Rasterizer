#pragma once
//#include "GeometricObj.h"
#include "Sphere.h"

#define X_PIXELS 512
#define Y_PIXELS 512

using namespace std;

class World
{
private:
	ImagePlane im_plane;
	std::vector<GeometricObj*> objects;
	Vector4 viewpoint;
	float view_dist;

	//Private utility functions
	float getMin(float f1, float f2, float f3);
	float getMax(float f1, float f2, float f3);
	int round(float f);

	//Properties of the view
	int x_pix;
	int y_pix;
	float left;
	float right;
	float bottom;
	float top;
	float near;
	float far;

	//For recomputing matrices
	arma::fmat cam_trans;
	arma::fmat persp_trans;
	arma::fmat ortho_proj;
	arma::fmat viewport_trans;

	void computeCam();
	void computePersp();
	void computeOrtho();
	void computeViewPort();

	void initMatr();
public:


	void writePixels(float to_write[X_PIXELS * Y_PIXELS * 3]);

	void addObject(GeometricObj& to_add);
	ImagePlane getImagePlane();
	void transform();
	void transformPartA();
	void transformPartB();
	void transformPartC();
	void transformPartD();
	~World();
	World();
};

#pragma once
#include "Material.h"
#include "Triangle.h"
#include "armadillo"
#include <vector>


//GeometricObj is any object that is approximated by a number of discrete triangles

class GeometricObj
{
protected:
	arma::fmat model_trans;
public:
	int num_triangles;
	std::vector<Triangle> triangles;

	virtual void transform(arma::fmat trans_matr);
	GeometricObj(void);
	~GeometricObj(void);
	Material surface_mat;
};


#include "GeometricObj.h"

GeometricObj::GeometricObj(void) :
	num_triangles(0),
	model_trans(arma::fmat(4, 4)),
	surface_mat(Material())
{
	triangles = (std::vector<Triangle>());
}


GeometricObj::~GeometricObj(void)
{
}


void GeometricObj::transform(arma::fmat trans_mat)
{
	for (int i = 0; i < triangles.size(); i++)
		triangles[i] = (triangles[i]).transform(trans_mat);
}
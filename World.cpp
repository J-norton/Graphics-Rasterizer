#include "World.h"


World::~World()
{
}

World::World() :
	x_pix(X_PIXELS),
	y_pix(Y_PIXELS),
	left(-0.1),
	right(0.1),
	bottom(-0.1),
	top(0.1),
	near(-0.1),
	far(-1000.0),
	viewpoint(Vector4()),
	objects(std::vector<GeometricObj*>()),
	im_plane(ImagePlane(X_PIXELS, Y_PIXELS)),
	cam_trans(arma::fmat(4, 4)),
	persp_trans(arma::fmat(4, 4)),
	ortho_proj(arma::fmat(4, 4)),
	viewport_trans(arma::fmat(4, 4))
{
	initMatr();
}

void World::addObject(GeometricObj& to_add)
{
	objects.push_back(&to_add);
}


void World::transformPartA()
{
	for (int i = 0; i < objects.size(); i++)
	{
		(*objects[i]).transform(persp_trans);
		(*objects[i]).transform(ortho_proj);
		(*objects[i]).transform(viewport_trans);
	}


	for (int i = 0; i < objects.size(); i++)
	{
		Material obj_color = (*objects[i]).surface_mat;
		for (int j = 0; j < (*objects[i]).num_triangles; j++)
		{
			Triangle cur_tri = (*objects[i]).triangles[j];
			Vector3 center = cur_tri.centroid;
			Vector3 tri_normal = (cur_tri.unit_normal[0] + cur_tri.unit_normal[1] + cur_tri.unit_normal[2]) / 3.0;

			//Back face culling
			if (tri_normal * (center) > 0.0)
				continue;

			Vector4 v1 = cur_tri.vertices[0];
			Vector4 v2 = cur_tri.vertices[1];
			Vector4 v3 = cur_tri.vertices[2];

			float xa = v1(0);
			float xb = v2(0);
			float xc = v3(0);
			float ya = v1(1);
			float yb = v2(1);
			float yc = v3(1);
			
			float x_min = floor(getMin(xa, xb, xc));
			float y_min = floor(getMin(ya, yb, yc));
			float x_max = ceil(getMax(xa, xb, xc));
			float y_max = ceil(getMax(ya, yb, yc));

	
			float n = x_max - x_min;

			for (int y = y_min; y <= y_max; y++)
			{
				for (int x = x_min; x <= x_max; x++)
				{
					float beta = ( (ya - yc) * x + (xc - xa) * y + xa * yc - xc * ya) / ( (ya - yc) * xb + (xc - xa) * yb + xa * yc - xc * ya);
					float gamma = ( (ya - yb) * x + (xb - xa) * y + xa * yb - xb * ya) / ( (ya - yb) * xc + (xb - xa) * yc + xa * yb - xb * ya);

					if (beta > 0.0 && gamma > 0.0 && (beta + gamma) < 1.0)
					{					
						im_plane.setPixel(x, y, Pixel(RGBColor(1, 1, 1), 1));
					}
				}
			}


		}
	}
}



void World::transformPartB()
{
	for (int i = 0; i < objects.size(); i++)
	{
		(*objects[i]).transform(persp_trans);
		(*objects[i]).transform(ortho_proj);
		(*objects[i]).transform(viewport_trans);
	}


	for (int i = 0; i < objects.size(); i++)
	{
		Material obj_color = (*objects[i]).surface_mat;
		for (int j = 0; j < (*objects[i]).num_triangles; j++)
		{
			Triangle cur_tri = (*objects[i]).triangles[j];
			Vector3 center = cur_tri.centroid;
			Vector3 tri_normal = (cur_tri.unit_normal[0] + cur_tri.unit_normal[1] + cur_tri.unit_normal[2]) / 3.0;

			//Back face culling
			if (tri_normal * (center) > 0.0)
				continue;

			Vector4 v1 = cur_tri.vertices[0];
			Vector4 v2 = cur_tri.vertices[1];
			Vector4 v3 = cur_tri.vertices[2];

			float xa = v1(0);
			float xb = v2(0);
			float xc = v3(0);
			float ya = v1(1);
			float yb = v2(1);
			float yc = v3(1);
			
			float x_min = floor(getMin(xa, xb, xc));
			float y_min = floor(getMin(ya, yb, yc));
			float x_max = ceil(getMax(xa, xb, xc));
			float y_max = ceil(getMax(ya, yb, yc));
	
			float n = x_max - x_min;

			for (int y = y_min; y <= y_max; y++)
			{
				for (int x = x_min; x <= x_max; x++)
				{
					float beta = ( (ya - yc) * x + (xc - xa) * y + xa * yc - xc * ya) / ( (ya - yc) * xb + (xc - xa) * yb + xa * yc - xc * ya);
					float gamma = ( (ya - yb) * x + (xb - xa) * y + xa * yb - xb * ya) / ( (ya - yb) * xc + (xb - xa) * yc + xa * yb - xb * ya);

					if (beta > 0.0 && gamma > 0.0 && (beta + gamma) < 1.0)
					{
						//Attribute interpolation ====================================================

						float d1 = cur_tri.world_vertices[0].getMagnitude();
						float d2 = cur_tri.world_vertices[1].getMagnitude();
						float d3 = cur_tri.world_vertices[2].getMagnitude();
						
						Vector3 fragment_location = center;
						

						Vector3 fragment_normal = fragment_location - Vector3(0, 0, -7);
						fragment_location = fragment_location / fragment_location.getMagnitude();

						fragment_normal = fragment_normal / fragment_normal.getMagnitude();

						float distance = (d1 + beta * (d2 - d1) + gamma * (d3 - d1)) / 3.0;

						//End of attribute interpolation ==============================================

						Vector3 light_vec = (Vector3(-4.0, 4.0, -3.0) / Vector3(-4.0, 4.0, -3.0).getMagnitude())
							- (fragment_location / fragment_location.getMagnitude());
						light_vec = light_vec / light_vec.getMagnitude();

						Vector3 h_spec = light_vec - (fragment_location / fragment_location.getMagnitude());
						h_spec = h_spec / h_spec.getMagnitude();

						RGBColor tri_color = getMax(0.0, 0.0, (fragment_normal * light_vec)) * obj_color.diffuse;
						tri_color = tri_color + (obj_color.ambient * 0.2);
						tri_color = tri_color + obj_color.specular * pow(getMax(0, 0, fragment_normal * h_spec), obj_color.phong_exponent);
						tri_color = tri_color.power(1.0 / 2.2);
						
						Pixel tri_pix = Pixel(tri_color, distance);

						if (tri_pix.depth < (im_plane.getPixel(x, y).depth - 0.001) || im_plane.getPixel(x, y).depth < 0.0)
							im_plane.setPixel(x, y, tri_pix);
					}
				}
			}


		}
	}
}


void World::transformPartD()
{
	for (int i = 0; i < objects.size(); i++)
	{
		(*objects[i]).transform(persp_trans);
		(*objects[i]).transform(ortho_proj);
		(*objects[i]).transform(viewport_trans);
	}


	for (int i = 0; i < objects.size(); i++)
	{
		Material obj_color = (*objects[i]).surface_mat;
		for (int j = 0; j < (*objects[i]).num_triangles; j++)
		{
			Triangle cur_tri = (*objects[i]).triangles[j];
			Vector3 center = cur_tri.centroid;
			Vector3 tri_normal = (cur_tri.unit_normal[0] + cur_tri.unit_normal[1] + cur_tri.unit_normal[2]) / 3.0;

			//Back face culling
			if (tri_normal * (center) > 0.0)
				continue;

			Vector4 v1 = cur_tri.vertices[0];
			Vector4 v2 = cur_tri.vertices[1];
			Vector4 v3 = cur_tri.vertices[2];

			float xa = v1(0);
			float xb = v2(0);
			float xc = v3(0);
			float ya = v1(1);
			float yb = v2(1);
			float yc = v3(1);
			
			float x_min = floor(getMin(xa, xb, xc));
			float y_min = floor(getMin(ya, yb, yc));
			float x_max = ceil(getMax(xa, xb, xc));
			float y_max = ceil(getMax(ya, yb, yc));
	
			float n = x_max - x_min;

			for (int y = y_min; y <= y_max; y++)
			{
				for (int x = x_min; x <= x_max; x++)
				{
					float beta = ( (ya - yc) * x + (xc - xa) * y + xa * yc - xc * ya) / ( (ya - yc) * xb + (xc - xa) * yb + xa * yc - xc * ya);
					float gamma = ( (ya - yb) * x + (xb - xa) * y + xa * yb - xb * ya) / ( (ya - yb) * xc + (xb - xa) * yc + xa * yb - xb * ya);

					if (beta > 0.0 && gamma > 0.0 && (beta + gamma) < 1.0)
					{						
						//Attribute interpolation ====================================================
						float d1 = cur_tri.world_vertices[0].getMagnitude();
						float d2 = cur_tri.world_vertices[1].getMagnitude();
						float d3 = cur_tri.world_vertices[2].getMagnitude();

						Vector3 norm_v1 = cur_tri.unit_normal[0];
						Vector3 norm_v2 = cur_tri.unit_normal[1];
						Vector3 norm_v3 = cur_tri.unit_normal[2];

						Vector4 vertex1 = cur_tri.world_vertices[0];
						Vector4 vertex2 = cur_tri.world_vertices[1];
						Vector4 vertex3 = cur_tri.world_vertices[2];

						Vector3 fragment_normal = norm_v1 + beta * (norm_v2 - norm_v1) + gamma * (norm_v3 - norm_v1);

						fragment_normal = fragment_normal / fragment_normal.getMagnitude();
						Vector4 temp = (vertex1  + beta * (vertex2 - vertex1)
							+ gamma * (vertex3 - vertex1));					


						//Vector4 temp = vertex1  + beta * (vertex2 - vertex1) + gamma * (vertex3 - vertex1);					
						
						Vector3 fragment_location = Vector3(temp(0), temp(1), temp(2));

						
						fragment_normal = fragment_normal / fragment_normal.getMagnitude();
						fragment_location = fragment_location / fragment_location.getMagnitude();

						float distance = (d1 + beta * d2 + gamma * d3) / 3.0;

						//End of attribute interpolation ==============================================

						Vector3 light_vec = (Vector3(-4.0, 4.0, -3.0) / Vector3(-4.0, 4.0, -3.0).getMagnitude())
							- (fragment_location / fragment_location.getMagnitude());
						light_vec = light_vec / light_vec.getMagnitude();

						//center = center / center.getMagnitude();
						Vector3 h_spec = light_vec - fragment_location;
						h_spec = h_spec / h_spec.getMagnitude();

						RGBColor tri_color = getMax(0.0, 0.0, (fragment_normal * light_vec)) * obj_color.diffuse;
						tri_color = tri_color + (obj_color.ambient * 0.2);
						tri_color = tri_color + obj_color.specular * pow(getMax(0, 0, fragment_normal * h_spec), obj_color.phong_exponent);
						tri_color = tri_color.power(1.0 / 2.2);
						
						Pixel tri_pix = Pixel(tri_color, distance);

						if (tri_pix.depth < (im_plane.getPixel(x, y).depth - 0.001) || im_plane.getPixel(x, y).depth < 0.0)
							im_plane.setPixel(x, y, tri_pix);
					}
				}
			}


		}
	}
}

void World::transformPartC()
{
	for (int i = 0; i < objects.size(); i++)
	{
		(*objects[i]).transform(persp_trans);
		(*objects[i]).transform(ortho_proj);
		(*objects[i]).transform(viewport_trans);
	}


	for (int i = 0; i < objects.size(); i++)
	{
		Material obj_color = (*objects[i]).surface_mat;
		for (int j = 0; j < (*objects[i]).num_triangles; j++)
		{
			Triangle cur_tri = (*objects[i]).triangles[j];
			Vector3 center = cur_tri.centroid;
			Vector3 tri_normal = (cur_tri.unit_normal[0] + cur_tri.unit_normal[1] + cur_tri.unit_normal[2]) / 3.0;

			//Back face culling
			if (tri_normal * (center) > 0.0)
				continue;

			Vector4 v1 = cur_tri.vertices[0];
			Vector4 v2 = cur_tri.vertices[1];
			Vector4 v3 = cur_tri.vertices[2];

			float xa = v1(0);
			float xb = v2(0);
			float xc = v3(0);
			float ya = v1(1);
			float yb = v2(1);
			float yc = v3(1);
			
			float x_min = floor(getMin(xa, xb, xc));
			float y_min = floor(getMin(ya, yb, yc));
			float x_max = ceil(getMax(xa, xb, xc));
			float y_max = ceil(getMax(ya, yb, yc));
	
			float n = x_max - x_min;

			for (int y = y_min; y <= y_max; y++)
			{
				for (int x = x_min; x <= x_max; x++)
				{
					float beta = ( (ya - yc) * x + (xc - xa) * y + xa * yc - xc * ya) / ( (ya - yc) * xb + (xc - xa) * yb + xa * yc - xc * ya);
					float gamma = ( (ya - yb) * x + (xb - xa) * y + xa * yb - xb * ya) / ( (ya - yb) * xc + (xb - xa) * yc + xa * yb - xb * ya);

					if (beta > 0.0 && gamma > 0.0 && (beta + gamma) < 1.0)
					{						
						//Attribute interpolation ====================================================
						float d1 = cur_tri.world_vertices[0].getMagnitude();
						float d2 = cur_tri.world_vertices[1].getMagnitude();
						float d3 = cur_tri.world_vertices[2].getMagnitude();


						Vector3 norm_vert[3];
						norm_vert[0] = cur_tri.unit_normal[0];
						norm_vert[1] = cur_tri.unit_normal[1];
						norm_vert[2] = cur_tri.unit_normal[2];

						Vector3 vert_loc[3];
						
						vert_loc[0] = Vector3(cur_tri.world_vertices[0](0), cur_tri.world_vertices[0](1), cur_tri.world_vertices[0](2));
						vert_loc[1] = Vector3(cur_tri.world_vertices[1](0), cur_tri.world_vertices[1](1), cur_tri.world_vertices[1](2));
						vert_loc[2] = Vector3(cur_tri.world_vertices[2](0), cur_tri.world_vertices[2](1), cur_tri.world_vertices[2](2));

						for (int m = 0; m < 3; m++)
						{
							vert_loc[m] = vert_loc[m] / vert_loc[m].getMagnitude();
							norm_vert[m] = norm_vert[m] / norm_vert[m].getMagnitude();
						}

						RGBColor to_return[3];
						float distance = (d1 + beta * d2 + gamma * d3) / 3.0;

						//End of attribute interpolation ==============================================
						for (int k = 0; k < 3; k++)
						{
							Vector3 light_vec = (Vector3(-4.0, 4.0, -3.0) / Vector3(-4.0, 4.0, -3.0).getMagnitude())
							- (vert_loc[k] / vert_loc[k].getMagnitude());
						light_vec = light_vec / light_vec.getMagnitude();

						//center = center / center.getMagnitude();
						Vector3 h_spec = light_vec - vert_loc[k];
						h_spec = h_spec / h_spec.getMagnitude();

						RGBColor tri_color = getMax(0.0, 0.0, (norm_vert[k] * light_vec)) * obj_color.diffuse;
						tri_color = tri_color + (obj_color.ambient * 0.2);
						tri_color = tri_color + obj_color.specular * pow(getMax(0, 0, norm_vert[k] * h_spec), obj_color.phong_exponent);
						//tri_color = tri_color.power(1.0 / 2.2);
						to_return[k] = tri_color;
						}
						
						RGBColor final_color = to_return[0] + (to_return[1] - to_return[0]) * beta + (to_return[2] - to_return[0]) * gamma;
						
						final_color = final_color.power(1.0 / 2.2);
						Pixel tri_pix = Pixel(final_color, distance);

						if (tri_pix.depth < (im_plane.getPixel(x, y).depth - 0.001) || im_plane.getPixel(x, y).depth < 0.0)
							im_plane.setPixel(x, y, tri_pix);
					}
				}
			}


		}
	}
}


inline float World::getMin(float f1, float f2, float f3)
{
	if (f1 <= f2 && f1 <= f3)
		return f1;
	
	if (f2 <= f3)
		return f2;

	return f3;
}


inline float World::getMax(float f1, float f2, float f3)
{
	if (f1 >= f2 && f1 >= f3)
		return f1;
	
	if (f2 >= f3)
		return f2;

	return f3;
}

inline int World::round(float f)
{
	return floor(f + 0.5);
}

ImagePlane World::getImagePlane()
{
	return im_plane;
}

void World::writePixels(float to_write[786432])
{
	im_plane.writePixels(to_write);
}

void World::initMatr()
{
	persp_trans(0, 0) = near;
	persp_trans(0, 1) = 0.0;
	persp_trans(0, 2) = 0.0;
	persp_trans(0, 3) = 0.0;

	persp_trans(1, 0) = 0.0;
	persp_trans(1, 1) = near;
	persp_trans(1, 2) = 0.0;
	persp_trans(1, 3) = 0.0;

	persp_trans(2, 0) = 0.0;
	persp_trans(2, 1) = 0.0;
	persp_trans(2, 2) = near + far;
	persp_trans(2, 3) = -(far * near);

	persp_trans(3, 0) = 0.0;
	persp_trans(3, 1) = 0.0;
	persp_trans(3, 2) = 1.0;
	persp_trans(3, 3) = 0.0;


	ortho_proj(0, 0) = 2.0 / (right - left);
	ortho_proj(0, 1) = 0.0;
	ortho_proj(0, 2) = 0.0;
	ortho_proj(0, 3) = -(right + left) / (right - left);

	ortho_proj(1, 0) = 0.0;
	ortho_proj(1, 1) = 2.0 / (top - bottom);
	ortho_proj(1, 2) = 0.0;
	ortho_proj(1, 3) = -(top + bottom) / (top - bottom);

	ortho_proj(2, 0) = 0.0;
	ortho_proj(2, 1) = 0.0;
	ortho_proj(2, 2) = 2.0 / (near - far);
	ortho_proj(2, 3) = -(near + far) / (near - far);

	ortho_proj(3, 0) = 0.0;
	ortho_proj(3, 1) = 0.0;
	ortho_proj(3, 2) = 0.0;
	ortho_proj(3, 3) = 1.0;


	viewport_trans(0, 0) = x_pix / 2.0;
	viewport_trans(0, 1) = 0.0;
	viewport_trans(0, 2) = 0.0;
	viewport_trans(0, 3) = (x_pix - 1.0) / 2.0;

	viewport_trans(1, 0) = 0.0;
	viewport_trans(1, 1) = y_pix / 2.0;
	viewport_trans(1, 2) = 0.0;
	viewport_trans(1, 3) = (y_pix - 1.0) / 2.0;

	viewport_trans(2, 0) = 0.0;
	viewport_trans(2, 1) = 0.0;
	viewport_trans(2, 2) = 1.0;
	viewport_trans(2, 3) = 0.0;

	viewport_trans(3, 0) = 0.0;
	viewport_trans(3, 1) = 0.0;
	viewport_trans(3, 2) = 0.0;
	viewport_trans(3, 3) = 1.0;
}
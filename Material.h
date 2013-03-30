#pragma once
#include "RGBColor.h"

class Material
{
public:
	RGBColor ambient;
	RGBColor diffuse;
	RGBColor specular;
	RGBColor reflective;

	float phong_exponent;

	Material(RGBColor amb, RGBColor diff, RGBColor spec, RGBColor refl);
	Material();
	~Material(void);
};
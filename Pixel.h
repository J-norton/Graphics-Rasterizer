#pragma once
#include "RGBColor.h"

class Pixel
{
public:
	float depth;
	RGBColor pix_color;
	Pixel(RGBColor color, float depth);

	Pixel(void);
	~Pixel(void);
};


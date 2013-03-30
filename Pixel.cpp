#include "Pixel.h"


Pixel::Pixel(void) :
	pix_color(RGBColor()),
	depth(-1.0)
{
}

Pixel::Pixel(RGBColor color, float depth) :
	pix_color(color),
	depth(depth)
{
}


Pixel::~Pixel(void)
{
}

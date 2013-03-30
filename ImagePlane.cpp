#include "ImagePlane.h"

ImagePlane::ImagePlane(int x_p, int y_p) :
	x(x_p),
	y(y_p)
{
	pixels = new Pixel[x_p * x_p];
}


ImagePlane::~ImagePlane(void)
{
}

Pixel ImagePlane::getPixel(int x_pos, int y_pos)
{
	return pixels[x_pos + x * y_pos];
}

float ImagePlane::getComponent(int x_pos, int y_pos, int color_channel)
{
	switch (color_channel)
	{
	case 0:
		return pixels[x_pos + x * y_pos].pix_color.red;
	case 1:
		return pixels[x_pos + x * y_pos].pix_color.green;
	case 2:
		return pixels[x_pos + x * y_pos].pix_color.blue;
	default:
		return 0.0;
	}
}

void ImagePlane::setPixel(int x_in, int y_in, Pixel p)
{
	pixels[x_in + x * y_in] = p;
}


void ImagePlane::writePixels(float to_gl[786432])
{
	int k = 0;
	for (int i = 0; i < x * y; i++)
	{
		to_gl[k * 3 ] = pixels[k].pix_color.red;
		to_gl[k * 3 + 1] = pixels[k].pix_color.green;
		to_gl[k * 3 + 2] = pixels[k++].pix_color.blue;
	}

	delete[] pixels;
}
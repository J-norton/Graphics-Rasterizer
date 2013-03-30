#pragma once
#include "Pixel.h"

class ImagePlane
{
private:
	Pixel* pixels;

public:
	Pixel getPixel(int x_pos, int y_pos);
	void writePixels(float values[512 * 512 * 3]);
	int x;
	int y;
	void setPixel(int x_pos, int y_pox, Pixel p);
	float getComponent(int x_pos, int y_pos, int color_channel);		//Returns the float value of the specified pixel + channel
	ImagePlane(int x, int y);
	~ImagePlane(void);
};


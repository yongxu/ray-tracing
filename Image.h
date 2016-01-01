#pragma once
#include"Color.h"

struct Image
{
	Color* image;
	int width, height;
	Image(Color *im, int width, int height)
		:image(im), width(width), height(height)
	{
	}
};


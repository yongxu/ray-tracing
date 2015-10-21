#pragma once
#include"numerics.h"
#include"Color.h"

struct Texture
{
	Color *texture;
	int width, height;
	Texture(Color *texture,int width, int height)
		:texture(texture), width(width), height(height)
	{
	}

	~Texture()
	{
		delete[] texture;
	}
};


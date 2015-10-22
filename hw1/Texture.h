#pragma once
#include <math.h>
#include"numerics.h"
#include"Color.h"
#include<iostream>
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

	const Color getColor(float u, float v) {
		int w = static_cast<int>(std::fmodf(std::fmodf(u, 1.0) + 1.0f, 1.0f)*width);
		int h = static_cast<int>(std::fmodf(std::fmodf(v, 1.0) + 1.0f, 1.0f)*height);

		int index = width*h + w;

		return texture[index];
	}
};


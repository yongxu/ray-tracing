#pragma once
#include<string>
#include"Color.h"
#include "numerics.h"
#include"Image.h"

namespace PPM {
	void generatePPM(Color* image, int width, int height, std::string filename);

	Image* readPPM(std::string fileName);
}


#pragma once
#include<string>
#include"MaterialColor.h"
#include "numerics.h"

namespace PPM {
	void generatePPM(Color* image, int width, int height, std::string filename);
}


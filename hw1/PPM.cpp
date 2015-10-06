#include "PPM.h"
#include <fstream>

void PPM::generatePPM(Color * image, int width, int height, std::string filename)
{
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::trunc);

	file << "P3\n" << width << " " << height << std::endl;
	file << "255\n";
	for (int i = 0; i < height;i++) {
		for (int j = 0; j < width;j++) {
			Color pixel = image[i*height + j];
			file << static_cast<int>(pixel.r*255) << " " << static_cast<int>(pixel.g*255) << " " << static_cast<int>(pixel.b*255) << " ";
		}
		file << "\n";
	}
	file.close();
}

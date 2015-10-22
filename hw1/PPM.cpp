#include "PPM.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

Image * PPM::readPPM(std::string fileName)
{
	std::ifstream inputFile(fileName);
	if (inputFile.bad()) {
		std::cout << "texture file:" << fileName << " invalid" << std::endl;
	}

	int width = 0, height = 0, colors = 0;
	bool header = false;

	Color* img = nullptr;
	int index = 0;

	while (!inputFile.eof()) {
		inputFile >> std::ws;
		std::string d;
		if (inputFile.peek() == '#') {
			inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else if (!header) {
			inputFile >> d;
			if (d == "P3") {
				header = true;
			}
			continue;
		}
		else if (!width) {
			try {
				inputFile >> width;
			}
			catch (...) {
				return nullptr;
			}
		}
		else if (!height) {
			try {
				inputFile >> height;
			}
			catch (...) {
				return nullptr;
			}
		}
		else if (!colors) {
			try {
				inputFile >> colors;
				img = new Color[width*height];
			}
			catch (...) {
				return nullptr;
			}
		}
		else if(img){
			//read color here
			int r, g, b;
			inputFile >> r >> g >> b;
			if(index<width*height)
				img[index++] = Color(r, g, b);

		}
	}
	inputFile.close();
	if (!img) {
		return nullptr;
	}
	return new Image(img, width, height);
}

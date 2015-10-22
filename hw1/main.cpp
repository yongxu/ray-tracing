#include<iostream>
#include<string>
#include"numerics.h"
#include"Parser.h"
#include"Scene.h"
#include"PPM.h"

int main(int argc, char *argv[]) {

	std::string input, output;
	if (argc == 2) {
		input = argv[1];
		output = std::string(argv[1]) + ".ppm";
	}
	else if (argc == 3) {
		input = argv[1];
		output =argv[2];
	}
	else {
		std::cout << "usage:" << "render " << "input" << " " << "output\n";
		return -1;
	}

	Parser p(input);
	Scene s(p);
	s.render();
	PPM::generatePPM(s.view, s.width, s.height, output);

	return 0;
}
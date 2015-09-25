#include "Parser.h"
#include "Sphere.h"
#include <cmath>

std::istream &operator>>(std::istream  &input, Vec3 &v)
{
	input >> v.x >> v.y >> v.z;
	return input;
}

Parser::Parser(std::string fileName)
	:inputFile{fileName},context{ std::make_shared<std::vector<std::shared_ptr<Shape>>>()}
{
	for (std::string d; inputFile >> d;) {
		if (d == "eye") {
			inputFile >> eye;
		}
		else if (d == "viewdir") {
			inputFile >> viewdir;
		}
		else if (d == "updir"){
			inputFile >> updir;
		}
		else if (d == "fovh") {
			inputFile >> fovh;
			//convert to rad
			fovh *= static_cast<float>(std::atan(1) * 4 / 180);
		}
		else if (d == "imsize") {
			inputFile >> width >> height;
		}
		else if (d == "bkgcolor") {
			float r, g, b;
			inputFile >> r >> g >> b;
			bkgcolor = Color(r, g, b);
		}
		else if (d == "mtlcolor") {
			float r, g, b;
			inputFile >> r >> g >> b;
			mtlcolor = Color(r, g, b);
		}
		else if (d == "sphere") {
			Vec3 center;
			float r;
			inputFile >> center;
			inputFile >> r;
			context->push_back(std::make_shared<Sphere>(center, r, mtlcolor));
		}
	}
}

Parser::~Parser()
{
}

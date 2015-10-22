#include "Parser.h"
#include "Sphere.h"
#include <cmath>
#include <sstream>

std::istream &operator>>(std::istream  &input, Vec3 &v)
{
	input >> v.x >> v.y >> v.z;
	return input;
}

Parser::Parser(std::string fileName)
	:inputFile{fileName},objects{ std::make_shared<std::vector<std::shared_ptr<Shape>>>()},
	lights{ std::make_shared<std::vector<std::shared_ptr<Light>>>() },
	textures{ std::make_shared<std::map<std::string,std::shared_ptr<Texture>>>() }
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
			std::string argLine;
			std::getline(inputFile, argLine);
			std::stringstream argStream;
			argStream << argLine;

			float Od_r, Od_g, Od_b;
			float Os_r, Os_g, Os_b;
			float ka, kd, ks, n;

			argStream >> Od_r >> Od_g >> Od_b
				>> Os_r >> Os_g >> Os_b
				>> ka >> kd >> ks >> n;
			mtlcolor = MaterialColor(Color(Od_r, Od_g, Od_b), Color(Os_r, Os_g, Os_b), ka, kd, ks, n);
		}
		else if (d == "sphere") {
			Vec3 center;
			float r;
			inputFile >> center;
			inputFile >> r;
			std::shared_ptr<Sphere> sphere;
			if(!currentTexture)
				sphere = std::make_shared<Sphere>(center, r, mtlcolor);
			else
				sphere = std::make_shared<Sphere>(center, r, mtlcolor,currentTexture);
			objects->push_back(sphere);
		}
		else if (d == "light") {
			float x, y, z, w, r, g, b;
			inputFile >> x >> y >> z >> w >> r >> g >> b;
			lights->push_back(std::make_shared<Light>(Vec3(x,y,z),w,Color(r,g,b)));
		}
		else if (d == "cylx") {
			std::string argLine;
			float y, z, r, xmin = 0, xmax = 0;
			std::getline(inputFile,argLine);
			std::stringstream argStream;
			argStream << argLine;
			argStream >> y >> z >> r >> xmin >> xmax;
			//TODO
			if (xmin == xmax) {
				std::cout << y << z << r << "\n";
			}else
				std::cout << y << z << r << xmin << xmax << "\n";
		}
		else if (d == "texture") {
			std::string name;
			inputFile >> name;
			Image* tx = PPM::readPPM(name);
			if (tx) {
				currentTexture = std::make_shared<Texture>(tx->image, tx->width, tx->height);
				(*textures)[name] = currentTexture;
			}
			else {
				currentTexture.reset();
			}
		}
	}
}

Parser::~Parser()
{
}

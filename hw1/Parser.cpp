#include "Parser.h"
#include "Sphere.h"
#include <cmath>
#include <sstream>
#include <regex>
#include"Triangle.h"

int matchToInt(std::sub_match<std::string::const_iterator> m) {
	return std::stoi(std::string(m.first, m.second));
}

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
			float ka, kd, ks, n, alpha, eta;

			argStream >> Od_r >> Od_g >> Od_b
				>> Os_r >> Os_g >> Os_b
				>> ka >> kd >> ks >> n >> alpha >> eta;
			mtlcolor = MaterialColor(Color(Od_r, Od_g, Od_b), Color(Os_r, Os_g, Os_b), ka, kd, ks, n, alpha, eta);
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
		else if (d == "v") {
			float x, y, z;
			inputFile >> x >> y >> z;
			vertices.push_back(Vec3(x, y, z));
		}
		else if (d == "vt") {
			float x, y;
			inputFile >> x >> y;
			vertices_t.push_back(Vec2(x, y));
		}
		else if (d == "vn") {
			float x, y, z;
			inputFile >> x >> y >> z;
			vertices_n.push_back(Vec3(x, y, z));
		}
		else if (d == "f") {
			std::string line;
			std::getline(inputFile, line);
			std::regex v("([0-9]+)\\s([0-9]+)\\s([0-9]+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
			std::regex v_vt("([0-9]+)/([0-9]+)\\s([0-9]+)/([0-9]+)\\s([0-9]+)/([0-9]+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
			std::regex v_vn("([0-9]+)//([0-9]+)\\s([0-9]+)//([0-9]+)\\s([0-9]+)//([0-9]+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
			std::regex v_vt_vn("([0-9]+)/([0-9]+)/([0-9]+)\\s([0-9]+)/([0-9]+)/([0-9]+)\\s([0-9]+)/([0-9]+)/([0-9]+)", std::regex_constants::ECMAScript | std::regex_constants::icase);
			
			std::smatch results;
			if (std::regex_search(line, results, v)) {
				Vec3 v1 = vertices[matchToInt(results[1]) - 1];

				Vec3 v2 = vertices[matchToInt(results[2]) - 1];

				Vec3 v3 = vertices[matchToInt(results[3]) - 1];

				objects->push_back(std::make_shared<Triangle>(v1, v2, v3, mtlcolor));
			}
			else if (std::regex_search(line, results, v_vt)) {
				Vec3 v1 = vertices[matchToInt(results[1]) - 1];
				Vec2 vt1 = vertices_t[matchToInt(results[2]) - 1];

				Vec3 v2 = vertices[matchToInt(results[3]) - 1];
				Vec2 vt2 = vertices_t[matchToInt(results[4]) - 1];

				Vec3 v3 = vertices[matchToInt(results[5]) - 1];
				Vec2 vt3 = vertices_t[matchToInt(results[6]) - 1];

				objects->push_back(std::make_shared<Triangle>(v1,v2,v3,vt1,vt2,vt3,mtlcolor, currentTexture));
			}
			else if (std::regex_search(line, results, v_vn)) {
				Vec3 v1 = vertices[matchToInt(results[1]) - 1];
				Vec3 vn1 = vertices_n[matchToInt(results[2]) - 1];

				Vec3 v2 = vertices[matchToInt(results[3]) - 1];
				Vec3 vn2 = vertices_n[matchToInt(results[4]) - 1];

				Vec3 v3 = vertices[matchToInt(results[5]) - 1];
				Vec3 vn3 = vertices_n[matchToInt(results[6]) - 1];

				objects->push_back(std::make_shared<Triangle>(v1, v2, v3, vn1, vn2, vn3, mtlcolor));
			}
			else if (std::regex_search(line, results, v_vt_vn)) {
				Vec3 v1 = vertices[matchToInt(results[1]) - 1];
				Vec2 vt1 = vertices_t[matchToInt(results[2]) - 1];
				Vec3 vn1 = vertices_n[matchToInt(results[3]) - 1];

				Vec3 v2 = vertices[matchToInt(results[4]) - 1];
				Vec2 vt2 = vertices_t[matchToInt(results[5]) - 1];
				Vec3 vn2 = vertices_n[matchToInt(results[6]) - 1];

				Vec3 v3 = vertices[matchToInt(results[7]) - 1];
				Vec2 vt3 = vertices_t[matchToInt(results[8]) - 1];
				Vec3 vn3 = vertices_n[matchToInt(results[9]) - 1];

				objects->push_back(std::make_shared<Triangle>(v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3, mtlcolor, currentTexture));

			}

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
		else if (d == "parallel") {
			parallel = true;
		}
	}
}

Parser::~Parser()
{
}

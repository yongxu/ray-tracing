#pragma once
#include<fstream>
#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include"numerics.h"
#include"MaterialColor.h"
#include"Shape.h"
#include"Light.h"

class Parser
{
public:
	Parser(std::string fileName);
	~Parser();

	std::shared_ptr<std::vector<std::shared_ptr<Shape>>> getObjects() {
		return objects;
	}

	Vec3 eye;
	Vec3 viewdir;
	Vec3 updir;
	float fovh;
	int width, height; //imsize
	Color bkgcolor;
	MaterialColor mtlcolor;
	std::shared_ptr<std::vector<std::shared_ptr<Shape>>> objects;
	std::shared_ptr<std::vector<std::shared_ptr<Light>>> lights;
private:
	std::ifstream inputFile;
};


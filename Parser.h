#pragma once
#include<fstream>
#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<map>
#include"numerics.h"
#include"Color.h"
#include"Shape.h"
#include"Light.h"
#include"Texture.h"
#include"Image.h"
#include"PPM.h"

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
	bool parallel = false;
	Color bkgcolor;
	MaterialColor mtlcolor;
	std::shared_ptr<Texture> currentTexture;
	std::shared_ptr<std::vector<std::shared_ptr<Shape>>> objects;
	std::shared_ptr<std::vector<std::shared_ptr<Light>>> lights;
	std::shared_ptr<std::map<std::string, std::shared_ptr<Texture>>> textures;

	std::vector<Vec3> vertices;
	std::vector<Vec2> vertices_t;
	std::vector<Vec3> vertices_n;
private:
	std::ifstream inputFile;
};


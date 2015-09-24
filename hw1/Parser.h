#pragma once
#include<fstream>
#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include"numerics.h"
#include"Shape.h"

class Parser
{
public:
	Parser(std::string fileName);
	~Parser();

	std::shared_ptr<std::vector<std::unique_ptr<Shape>>> getContext() {
		return context;
	}

	Vec3 eye;
	Vec3 viewdir;
	Vec3 updir;
	float fovh;
	int width, height; //imsize
	Color bkgcolor;
	Color mtlcolor;
	std::shared_ptr<std::vector<std::unique_ptr<Shape>>> context;
private:
	std::ifstream inputFile;
};


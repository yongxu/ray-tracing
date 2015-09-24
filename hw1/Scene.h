#pragma once
#include "Parser.h"
class Scene
{
public:
	Scene(const Parser &p):Scene(p, 10) {} //default pixels_per_unit
	Scene(const Parser &,const float);
	~Scene();
private:
	//those are from Parser
	Vec3 eye;
	Vec3 viewdir;
	Vec3 updir;
	float fovh;
	int width, height; //imsize
	Color bkgcolor;
	Color mtlcolor;
	std::shared_ptr<std::vector<std::unique_ptr<Shape>>> context;

	float pixels_per_unit;
	float pixel_size;
	float w, h;//width height calculated from pixels_per_unit
	float *view;
	float fovv; //fov vertical
	Vec3 viewCenter;
	float d; //eye to view distance
	float aspectRatio;

	//upper left, upper right, lower left, lower right of view
	Vec3 ul, ur, ll, lr;

};


#pragma once
#include "Parser.h"
class Scene
{
public:
	Scene(const Parser &p):Scene(p, 1, 3) {} //default pixels_per_unit
	Scene(const Parser &, const float, const int rayBounceTimes);
	~Scene();

	int width, height; //imsize
	Color *view;
	Color* render();
private:
	//those are from Parser
	Vec3 eye;
	Vec3 viewdir;
	Vec3 updir;
	float fovh;
	Color bkgcolor;
	//Color mtlcolor;
	std::shared_ptr<std::vector<std::shared_ptr<Shape>>> objects;
	std::shared_ptr<std::vector<std::shared_ptr<Light>>> lights;
	std::shared_ptr<std::map<std::string, std::shared_ptr<Texture>>> textures;

	float pixels_per_unit;
	float pixel_size;
	float w, h;//width height calculated from pixels_per_unit
	float fovv; //fov vertical
	Vec3 viewCenter;
	float d; //eye to view distance
	float aspectRatio;
	bool parallel;

	int rayBounceTimes;
	//upper left, upper right, lower left, lower right of view
	Vec3 ul, ur, ll, lr;
	//unit vector along view
	Vec3 u, v;
	Color traceRay(const Ray& ray, float refractionIndex = 1, int iteration = 0, Shape * from = nullptr);

};


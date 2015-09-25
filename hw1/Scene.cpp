#include "Scene.h"
#include <cmath>
#include <limits>
using namespace std;

Scene::Scene(const Parser & p,const float ppu)
	:eye{p.eye},viewdir{p.viewdir.normlize()},updir{p.updir.normlize()},fovh{p.fovh},
	 width{p.width},height{p.height},bkgcolor{p.bkgcolor},context{p.context},pixels_per_unit{ppu}
{
	view = new Color[width*height];
	u = viewdir.cross(updir);
	v = u.cross(viewdir);

	//real width and hight calculated
	w = width / pixels_per_unit;
	h = height / pixels_per_unit;

	pixel_size = static_cast<float>(1.0 / pixels_per_unit);

	//eye to view distance
	d = w / 2 / tan(fovh / 2);

	aspectRatio = w / h;

	fovv = 2 * atan2(w / 2, d);
	viewCenter = eye + viewdir * d;

	//upper left, upper right, lower left, lower right of view
	ul = viewCenter - u * (w / 2) + v * (h / 2);
	ur = viewCenter + u * (w / 2) + v * (h / 2);
	ll = viewCenter - u * (w / 2) - v * (h / 2);
	lr = viewCenter + u * (w / 2) - v * (h / 2);
}

Scene::~Scene()
{
	delete[] view;
}

Color Scene::traceRay(const Vec3& ray)
{
	//normalize ray
	Vec3 d = ray.normlize();
	Color c = bkgcolor;
	float min = std::numeric_limits<float>::max();
	for (auto shape : *context ) {
		Color temp_c;
		float t = shape->traceRay(d, eye, temp_c);
		if (t > 0 && t < min) {
			min = t;
			c = temp_c;
		}
	}
	return c;
}

Color * Scene::render()
{
	for (int i = 0; i < height;i++) {
		for (int j = 0; j < width;j++) {
			//calculate each pixel position in scene coordinate
			Vec3 p = ul + u * i - v * j;
			//calculate ray vector, from eye to view
			Vec3 ray = p - eye;
			//trace ray to find pixel color
			view[i*height + j] = traceRay(ray);
		}
	}
	return view;
}

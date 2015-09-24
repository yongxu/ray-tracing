#include "Scene.h"
#include <cmath>
using namespace std;

Scene::Scene(const Parser & p,const float ppu)
	:eye{p.eye},viewdir{p.viewdir.normlize()},updir{p.updir.normlize()},fovh{p.fovh},
	 width{p.width},height{p.height},bkgcolor{p.bkgcolor},context{p.context},pixels_per_unit{ppu}
{
	view = new float[width*height];
	Vec3 u = viewdir.cross(updir);
	Vec3 v = u.cross(viewdir);

	//real width and hight calculated
	w = width / pixels_per_unit;
	h = height / pixels_per_unit;

	pixel_size = 1.0 / pixels_per_unit;

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

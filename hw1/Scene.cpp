#include "Scene.h"
#include <cmath>
#include <limits>
using namespace std;

Scene::Scene(const Parser & p,const float ppu, const int rayBounceTimes)
	:eye{p.eye},viewdir{p.viewdir.normlize()},updir{p.updir.normlize()},fovh{p.fovh},
	 width{p.width},height{p.height},bkgcolor{p.bkgcolor}, objects{ p.objects },
	lights{ p.lights }, textures{ p.textures }, parallel{ p.parallel }, pixels_per_unit{ ppu },
	rayBounceTimes{rayBounceTimes}
{
	view = new Color[width*height];
	u = viewdir.cross(updir).normlize();
	v = u.cross(viewdir).normlize();

	//real width and hight calculated
	w = width / pixels_per_unit;
	h = height / pixels_per_unit;

	pixel_size = static_cast<float>(1.0 / pixels_per_unit);

	//eye to view distance
	d = w / 2 / tan(fovh / 2);

	aspectRatio = w / h;

	if (parallel) {
		d = 0;
	}

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

Color Scene::traceRay(const Ray& ray, float refractionIndex, int iteration)
{
	//normalize ray
	float min_t = std::numeric_limits<float>::max();
	Shape *closest = nullptr;
	for (auto shape : *objects) {
		float t = shape->hit(ray);
		if (t > 0 && t < min_t) {
			min_t = t;
			closest = shape.get();
		}
	}
	if (!closest) {
		return iteration == rayBounceTimes ? bkgcolor : Color(0,0,0);
	}
	//shading
	const Ray v = Ray{ -ray.dir, ray.reach(min_t) };
	ColorIntrinsics intrinsics = closest->getIntrinsics(v);
	Color Od = intrinsics.Od;
	Color Os = intrinsics.Os;
	float ka = intrinsics.ka;
	float kd = intrinsics.kd;
	float ks = intrinsics.ks;
	float n_s = intrinsics.n;
	float alpha = intrinsics.alpha;
	float eta = intrinsics.eta;
	const Vec3 n = intrinsics.normal;
	Color L = Od*ka;

	for (auto light : *lights) {
		Vec3 l = light->direction(v.pos);
		bool shadow = false;
		for (auto shape : *objects) {
			if (shape.get() == closest)
				continue;
			float t = shape->hit(Ray{l,v.pos});
			if (light->isBlocked(v.pos,l,t)) {
				shadow = true;
				break;
			}
		}
		if (shadow)
			continue;
		Vec3 h = (l + v.dir).normlize();
		Color diffuse = Od*kd*std::fmax(0.f, n*l);
		Color specular = Os*ks*std::pow(std::fmax(0.f, n*h),n_s);
		L += light->color*(diffuse + specular);
	}
	if (iteration) {
		//reflection
		Color R = traceRay(Ray{ v.dir.reflect(n) , v.pos }, refractionIndex, iteration -1);
		float cos_theta = std::fmax(0.f, v.dir*n);
		float F_0 = std::pow((eta- refractionIndex)/ (eta + refractionIndex),2);
		float F_r = F_0 + (1 - F_0)*std::pow(1.0f - cos_theta, 5.0f);
		//std::cout << eta <<" " << cos_theta << " " << "\n";
		L += R.normalize() * F_r;

		//refrection
		if (alpha >= 0 && alpha <= 1.0) {
			Vec3 T = (-n)*std::sqrt(1.0f - std::pow(refractionIndex / eta, 2)*(1 - cos_theta*cos_theta))
				+ (n*cos_theta - v.dir)*(refractionIndex / eta);
			L += traceRay(Ray{ T , v.pos }, eta, iteration - 1)*(1-F_r)*(1-alpha);
		}
	}
	return L;
}

Color * Scene::render()
{
	if (parallel){
		for (int i = 0; i < width;i++) {
			for (int j = 0; j < height;j++) {
				Vec3 p = ul + u * i - v * j;
				view[j*height + i] = traceRay(Ray{ viewdir,p });
			}
		}
	}
	else {
		for (int i = 0; i < width;i++) {
			for (int j = 0; j < height;j++) {
				//calculate each pixel position in scene coordinate
				Vec3 p = ul + u * i - v * j;
				//calculate ray vector, from eye to view
				Vec3 ray = p - eye;
				//trace ray to find pixel color
				view[j*height + i] = traceRay(Ray{ ray.normlize(),eye }, 1.0, rayBounceTimes).clamp();
			}
		}
	}
	return view;
}

#include "Sphere.h"
#include <cmath>

Sphere::~Sphere()
{
}

float Sphere::traceRay(const Vec3 & ray, const Vec3 & eye, Color & color)
{
	//solve quadratic equation
	Vec3 c2eye = eye - this->c;
	//a = 1
	float b = (ray*c2eye) * 2;
	float c = c2eye.lengthSquare() - r*r;

	float delta2 = b*b - 4 * c;

	if (delta2 > 0) {
		color = this->color;
		return (-b + std::sqrt(delta2)) / 2;
	}

	return -1.0;
}

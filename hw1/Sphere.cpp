#include "Sphere.h"
#include <cmath>
#include<iostream>
Sphere::~Sphere()
{
}

float Sphere::hit(const Ray &ray)
{
	//solve quadratic equation
	Vec3 r2eye = ray.pos - center;
	//a = 1
	float b = (ray.dir*r2eye) * 2;
	float c = r2eye.lengthSquare() - r2;
	float delta2 = b*b - 4 * c;
	//std::cout << ray.x<<" "<< ray.y << " " << ray.z << " " << "\n";

	if (delta2 >= 0) {
		return (-b - std::sqrt(delta2)) / 2;
	}
	return -1.0;
}

const Vec3 Sphere::surfaceNormal(const Ray & ray)
{
	return (ray.pos - center).normlize();
}

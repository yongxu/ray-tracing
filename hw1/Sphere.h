#pragma once
#include "Shape.h"
#include"numerics.h"
#include"MaterialColor.h"
class Sphere :
	public Shape
{
public:
	Sphere(Vec3 center, float radius, MaterialColor color) :
		center{ center }, r{ radius }, Shape(color)
	{
		r2 = radius*radius;
	}
	~Sphere() override;

	Vec3 center;
	float r;
	float r2;

	float hit(const Ray &ray) override;
	const Vec3& surfaceNormal(const Ray &ray) override;
};


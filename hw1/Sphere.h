#pragma once
#include "Shape.h"
#include"numerics.h"
class Sphere :
	public Shape
{
public:
	Sphere(Vec3 center, float radius, Color col) :
		c{ center }, r{ radius }, color{ col }
	{}
	~Sphere() override;

	Vec3 c;
	Color color;
	float r;
	
};


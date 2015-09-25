#pragma once
#include "numerics.h"
class Shape
{
public:
	virtual ~Shape() {};
	//return the distance between the point ray hits on shape and it's color
	//if didn't hit or behind eye, return t<0
	//ray: unit vector
	virtual float traceRay(const Vec3& ray, const Vec3& eye, Color& c) =0;
};


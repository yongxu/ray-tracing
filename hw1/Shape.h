#pragma once
#include "numerics.h"
#include"MaterialColor.h"
class Shape
{
public:
	Shape() {};
	Shape(MaterialColor c) :color(c) {};
	virtual ~Shape() {};
	//return the distance between the point ray hits on shape and it's color
	//if didn't hit or behind eye, return t<0
	//ray: unit vector
	virtual float hit(const Ray &ray) = 0;
	virtual const Vec3& surfaceNormal(const Ray &ray) = 0;
	MaterialColor color;
};


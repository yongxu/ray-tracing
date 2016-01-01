#pragma once
#include "Shape.h"
#include"numerics.h"
#include"Color.h"

class Light
{
public:
	Light(Vec3 position, float w, Color color) :
		pos{ position }, w{ w }, color(color)
	{
	}

	inline const Vec3 direction(const Vec3 & from) const {
		if (!w)
			return (pos - from).normlize();
		else
			return pos.normlize();
	}
	inline bool isBlocked(const Vec3 & from,const Vec3 & direction,const float distance) const {
		if (w && distance>0)
			return true;
		else if (distance > 0 &&
			(from + direction*distance).quadrance() < (pos - from).quadrance())
			return true;
		else
			return false;
	}


	Vec3 pos;
	float w;
	Color color;

};


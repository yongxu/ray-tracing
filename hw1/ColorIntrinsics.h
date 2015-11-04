#pragma once
#include"numerics.h"
#include"Color.h"
struct ColorIntrinsics
{
	Color Od;
	Color Os;
	float ka, kd, ks, n, alpha, eta;
	Vec3 normal;
	ColorIntrinsics() {};
	ColorIntrinsics(Color Od, Color Os, float ka, float kd, float ks, float n, float alpha = 1.0f, float eta = 0.0f)
		: Od{ Od }, Os{ Os }, ka{ ka }, kd{ kd }, ks{ ks }, n{ n }, alpha{ alpha }, eta{ eta }
	{
	}
	ColorIntrinsics(const MaterialColor color)
		: Od{ color.Od }, Os{ color.Os }, ka{ color.ka }, kd{ color.kd }, ks{ color.ks }, n{ color.n }, alpha{ alpha }, eta{ eta }
	{
	}
	ColorIntrinsics(const MaterialColor color,Vec3 normal)
		: Od{ color.Od }, Os{ color.Os }, ka{ color.ka }, kd{ color.kd }, ks{ color.ks }, n{ color.n }, alpha{ alpha }, eta{ eta }, normal(normal)
	{
	}
};


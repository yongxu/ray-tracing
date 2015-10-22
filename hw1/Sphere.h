#pragma once
#include<memory>
#include "Shape.h"
#include"numerics.h"
#include"Color.h"
#include"ColorIntrinsics.h"
#include"Texture.h"
class Sphere :
	public Shape
{
public:
	Sphere(Vec3 center, float radius, MaterialColor color) :
		Sphere(center, radius, color, nullptr)
	{
		r2 = radius*radius;
	}
	Sphere(Vec3 center, float radius, MaterialColor color, std::shared_ptr<Texture> tx) :
		center{ center }, r{ radius }, materialColor(color), texture(tx), intrinsics(color)
	{
		r2 = radius*radius;
	}
	~Sphere() override;

	Vec3 center;
	float r;
	float r2;
	MaterialColor materialColor;
	std::shared_ptr<Texture> texture;
	ColorIntrinsics intrinsics;


	float hit(const Ray &ray) override;
	const Vec3 surfaceNormal(const Ray &ray) override;
	const ColorIntrinsics& getIntrinsics(const Ray &ray) override;
};


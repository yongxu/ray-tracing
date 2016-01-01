#pragma once
#include<memory>
#include "Shape.h"
#include"numerics.h"
#include"Color.h"
#include"ColorIntrinsics.h"
#include"Texture.h"
class Triangle :
	public Shape
{
public:
	Triangle(Vec3 v1, Vec3 v2, Vec3 v3,
			 MaterialColor materialColor);

	Triangle(Vec3 v1, Vec3 v2, Vec3 v3,
			 Vec3 vn1, Vec3 vn2, Vec3 vn3,
			 MaterialColor materialColor);

	Triangle(Vec3 v1, Vec3 v2, Vec3 v3,
			 Vec2 vt1, Vec2 vt2, Vec2 vt3,
			 MaterialColor materialColor,
			 std::shared_ptr<Texture> tx);

	Triangle(Vec3 v1, Vec3 v2, Vec3 v3,
			 Vec2 vt1, Vec2 vt2, Vec2 vt3,
			 Vec3 vn1, Vec3 vn2, Vec3 vn3,
			 MaterialColor materialColor,
			 std::shared_ptr<Texture> tx);

	
	Vec3 v1, v2, v3;
	Vec2 vt1, vt2, vt3;
	Vec3 vn1, vn2, vn3;
	
	Vec3 normal;

	MaterialColor materialColor;
	std::shared_ptr<Texture> texture;
	ColorIntrinsics intrinsics;

	float hit(const Ray &ray) override;
	const Vec3 surfaceNormal(const Ray &ray) override;
	const ColorIntrinsics& getIntrinsics(const Ray &ray) override;
private:
	float a, b, c, d, e, f, beta, gamma;
	bool smoothShading = false;
	void find_abcdef(Vec3 p0,Vec3 p1,Vec3 p2);
};


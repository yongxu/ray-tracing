#include "Triangle.h"

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, MaterialColor materialColor)
	: v1(v1), v2(v2), v3(v3), materialColor(materialColor), texture(nullptr)
{
	smoothShading = false;

	Vec3 e1 = v2 - v1;
	Vec3 e2 = v3 - v1;

	normal = e1.cross(e2).normlize();

	intrinsics = ColorIntrinsics(materialColor, normal);

	find_abcdef(v1, v2, v3);
}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec3 vn1, Vec3 vn2, Vec3 vn3, MaterialColor materialColor)
	: v1(v1), v2(v2), v3(v3), vn1(vn1), vn2(vn2), vn3(vn3), materialColor(materialColor), texture(nullptr)
{
	smoothShading = true;

	Vec3 e1 = v2 - v1;
	Vec3 e2 = v3 - v1;

	normal = e1.cross(e2).normlize();

	intrinsics = ColorIntrinsics(materialColor, normal);

	find_abcdef(v1, v2, v3);
}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec2 vt1, Vec2 vt2, Vec2 vt3, MaterialColor materialColor, std::shared_ptr<Texture> tx)
	: v1(v1), v2(v2), v3(v3), vt1(vt1), vt2(vt2), vt3(vt3), materialColor(materialColor), texture(tx)
{
	Vec3 e1 = v2 - v1;
	Vec3 e2 = v3 - v1;

	normal = e1.cross(e2).normlize();

	intrinsics = ColorIntrinsics(materialColor, normal);

	find_abcdef(v1, v2, v3);
}

Triangle::Triangle(Vec3 v1, Vec3 v2, Vec3 v3, Vec2 vt1, Vec2 vt2, Vec2 vt3, Vec3 vn1, Vec3 vn2, Vec3 vn3, MaterialColor materialColor, std::shared_ptr<Texture> tx)
	: v1(v1), v2(v2), v3(v3), vt1(vt1), vt2(vt2), vt3(vt3), vn1(vn1), vn2(vn2), vn3(vn3), materialColor(materialColor), texture(tx)
{
	smoothShading = true;

	Vec3 e1 = v2 - v1;
	Vec3 e2 = v3 - v1;

	normal = e1.cross(e2).normlize();

	intrinsics = ColorIntrinsics(materialColor, normal);

	find_abcdef(v1, v2, v3);
}

float Triangle::hit(const Ray & ray)
{
	float g = ray.dir.x;
	float h = ray.dir.y;
	float i = ray.dir.z;

	Vec3 jkl = v1 - ray.pos;
	float j = jkl.x, k = jkl.y, l = jkl.z;

	float m = e*i - h*f;
	float n = g*f - d*i;
	float o = d*h - e*g;

	float p = a*k - j*b;
	float q = j*c - a*l;
	float r = b*l - k*c;

	float s = a*m + b*n + c*o;

	float t = -(f*p + e*q + d*r) / s;

	if (t <= 0) return 0.0f;

	gamma = (i*p + h*q + g*r) / s;

	if (!(gamma>=0 && gamma<1)) return 0.0f;

	beta = (j*m + k*n + l*o) / s;

	if (0 <= beta && beta <= (1 - gamma)) {
		return t; //intersected!
	}

	return 0.0f;
}

const Vec3 Triangle::surfaceNormal(const Ray & ray)
{
	return normal;
}

const ColorIntrinsics & Triangle::getIntrinsics(const Ray & ray)
{
	float alpha = 1 - beta - gamma;
	if (smoothShading) {
		intrinsics.normal = (vn1*alpha + vn2*beta + vn3*gamma).normlize();
	}
	if (!texture) {
		intrinsics.Od = materialColor.Od;
	}
	else {
		float u = alpha*vt1.x + beta*vt2.x + gamma*vt3.x;
		float v = alpha*vt1.y + beta*vt2.y + gamma*vt3.y;
		Color color = texture->getColor(u, v);
		intrinsics.Od = color;
	}
	return intrinsics;
}

void Triangle::find_abcdef(Vec3 p0, Vec3 p1, Vec3 p2)
{
	Vec3 abc = p0 - p1;
	Vec3 def = p0 - p2;
	a = abc.x;
	b = abc.y;
	c = abc.z;
	d = def.x;
	e = def.y;
	f = def.z;
}

#pragma once
#include<cmath>
struct Vec3
{
	float x, y, z;
	Vec3():x{0},y{0},z{0} {}
	Vec3(float x,float y,float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	inline float operator*(const Vec3& rhs) const {
		return this->x*rhs.x + this->y*rhs.y + this->z*rhs.z;
	}
	inline Vec3 operator+(const Vec3& rhs) const {
		return{ this->x+rhs.x,this->y+rhs.y,this->z+rhs.z };
	}
	inline Vec3 operator-(const Vec3& rhs) const {
		return{ this->x - rhs.x,this->y - rhs.y,this->z - rhs.z };
	}
	inline Vec3 operator*(const float& rhs) const {
		return{ this->x*rhs,this->y*rhs,this->z*rhs };
	}
	inline Vec3 operator*(const int& rhs) const {
		return{ this->x*rhs,this->y*rhs,this->z*rhs };
	}
	inline Vec3 operator/(const float& rhs) const {
		return{ this->x/rhs,this->y/rhs,this->z/rhs };
	}
	inline Vec3 operator+(const float& rhs) const {
		return{ this->x + rhs,this->y + rhs,this->z + rhs };
	}
	inline Vec3 operator-(const float& rhs) const {
		return{ this->x - rhs,this->y - rhs,this->z - rhs };
	}
	inline Vec3 cross(const Vec3& rhs) const {
		return{ (this->y * rhs.z) - (this->z * rhs.y),
				(this->z * rhs.x) - (this->x * rhs.z),
				(this->x * rhs.y) - (this->y * rhs.x) };
	}
	inline float distanceSqare(const Vec3& rhs) const {
		float dx = rhs.x - x;
		float dy = rhs.y - y;
		float dz = rhs.z - z;
		return dx*dx + dy*dy + dz*dz;
	}
	inline float distance(const Vec3& rhs) const {
		return distanceSqare(rhs);
	}

	inline float lengthSquare() const {
		return x*x + y*y + z*z;
	}
	inline float length() const {
		return std::sqrt(lengthSquare());
	}
	inline Vec3 normlize() const {
		float len = length();

		return len ? *this / len : Vec3{0, 0, 0};
	}
	
};

struct Vec2
{
	float x, y;
	inline Vec2 operator*(const Vec2& rhs) {
		return{ this->x*rhs.x,this->y*rhs.y};
	}
	inline Vec2 operator+(const Vec2& rhs) {
		return{ this->x+rhs.x,this->y+rhs.y };
	}
	inline Vec2 operator*(const float& rhs) {
		return{ this->x*rhs,this->y*rhs };
	}
	inline Vec2 operator+(const float& rhs) {
		return{ this->x + rhs,this->y + rhs };
	}
};

using Point = Vec3;

struct Color {
	union {
		unsigned int c;
		struct {
			unsigned char a;
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};
	};
	Color() 
		:a{ 255 }, r{ 0 }, g{ 0 }, b{ 0 }
	{
	}
	Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color(unsigned char r, unsigned char g, unsigned char b) {
		this->a = 255;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color(float a,float r, float g, float b) {
		this->a = static_cast<unsigned char>(255 * a);
		this->r = static_cast<unsigned char>(255 * r);
		this->g = static_cast<unsigned char>(255 * g);
		this->b = static_cast<unsigned char>(255 * b);
	}
	Color(float r, float g, float b) {
		this->a = 255;
		this->r = static_cast<unsigned char>(255 * r);
		this->g = static_cast<unsigned char>(255 * g);
		this->b = static_cast<unsigned char>(255 * b);
	}
};
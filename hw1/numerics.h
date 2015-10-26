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
	inline Vec3 operator-() const {
		return{ -x,-y,-z };
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

	inline float quadrance() const {
		return x*x + y*y + z*z;
	}
	inline float length() const {
		return std::sqrt(quadrance());
	}
	inline Vec3 normlize() const {
		float len = length();

		return len ? *this / len : Vec3{0, 0, 0};
	}
	
};

struct Ray {
	Vec3 dir;
	Vec3 pos;
	inline Vec3 reach(float t) const {
		return pos + (dir*t);
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
	Vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}
	Vec2() :Vec2(0, 0) {}
};


const float PI = 3.141592653589793238462643383279502884f;
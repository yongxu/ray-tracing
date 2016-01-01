#pragma once

struct Color {
	float a;
	float r;
	float g;
	float b;
	Color()
		:a{ 1.0 }, r{ 0 }, g{ 0 }, b{ 0 }
	{
	}
	Color(float a, float r, float g, float b) {
		this->a = a;
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color(float r, float g, float b) {
		this->a = 1.0f;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	Color(unsigned char r, unsigned char g, unsigned char b) {
		this->a = 1;
		this->r = static_cast<float>(r / 255.0);
		this->g = static_cast<float>(g / 255.0);
		this->b = static_cast<float>(b / 255.0);
	}
	Color(int r, int g, int b) {
		this->a = 1;
		this->r = static_cast<float>(r / 255.0);
		this->g = static_cast<float>(g / 255.0);
		this->b = static_cast<float>(b / 255.0);
	}
	Color(unsigned char a, unsigned char r, unsigned char g, unsigned char b) {
		this->a = static_cast<float>(a / 255.0);
		this->r = static_cast<float>(r / 255.0);
		this->g = static_cast<float>(g / 255.0);
		this->b = static_cast<float>(b / 255.0);
	}
	inline Color operator*(const Color& rhs) const {
		return Color(a*rhs.a, r*rhs.r, g*rhs.g, b*rhs.b);
	}
	inline Color operator+(const Color& rhs) const {
		return Color(a, r+rhs.r, g+rhs.g, b+rhs.b);
	}
	inline Color operator*(const float& rhs) const {
		return{ this->r*rhs,this->g*rhs,this->b*rhs };
	}
	inline Color operator/(const float& rhs) const {
		return{ this->r / rhs,this->g / rhs,this->b / rhs };
	}
	inline Color operator+(const float& rhs) const {
		return{ this->r + rhs,this->g + rhs,this->b + rhs };
	}
	inline void operator+=(const Color& rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
	}
	inline Color clamp() {
		return{
			r > 1.0f ? 1.0f : r < 0.0f ? 0.0f : r,
			g > 1.0f ? 1.0f : g < 0.0f ? 0.0f : g,
			b > 1.0f ? 1.0f : b < 0.0f ? 0.0f : b
		};
	}

	inline Color normalize() {
		float max = r > g ? r >b ? r : b : g > b? g : b;
		if (max > 1.0f)
			return{
				r / max,
				g / max,
				b / max
		};
		else
			return *this;
	}
};

struct MaterialColor
{
	Color Od;
	Color Os;
	float ka, kd, ks, n, alpha, eta;
	MaterialColor() {};
	MaterialColor(Color Od,Color Os,float ka,float kd,float ks,float n, float alpha, float eta)
		: Od{Od}, Os{Os}, ka{ka}, kd{kd}, ks{ks}, n{n}, alpha{alpha}, eta{eta}
	{
	}

};


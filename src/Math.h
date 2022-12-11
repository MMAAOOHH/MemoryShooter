#pragma once

struct Vec2
{
	Vec2()
		: x(0.f), y(0.f)	{}
	Vec2(float x, float y)
		: x(x), y(y)		{}
	Vec2(float x)
		: x(x), y(x)		{}

	float x;
	float y;

	// Operator overloads
	Vec2 operator+(Vec2 const& v) const
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 operator+=(Vec2 const& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	Vec2 operator-(Vec2 const& v) const
	{
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 operator-=(Vec2 const& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	Vec2 operator*(Vec2 const& v) const
	{
		return Vec2(x * v.x, y * v.y);
	}
	Vec2 operator*(float const& scalar) const
	{
		return Vec2(x * scalar, y * scalar);
	}

	Vec2 operator/(float const& scalar) const
	{
		return Vec2(x / scalar, y / scalar);
	}

};

inline float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}


//inline Vec2 lerp(Vec2 a, Vec2 b, float t)
//{
//	float x = a.x + t * (b.x - a.x);
//	float y = a.y + t * (b.y - a.y);
//	return Vec2
//}

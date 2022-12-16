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

	void normalized() 
	{
		float length = sqrt((x * x) + (y * y));
		x /= length;
		y /= length;
	}

	void normalize(Vec2& my_vec)
	{
		float length = sqrt((x * x) + (y * y));
		my_vec.x = my_vec.x / length;
		my_vec.y = my_vec.y / length;
	}

	//Vec2 normalize(Vec2 const& v)
	//{
	//	float length = sqrt((v.x * v.x) + (v.y * v.y));
	//	return Vec2(v.x / length, v.y / length);
	//}


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

inline Vec2 lerp(Vec2 a, Vec2 b, float t)
{
	float x = (1 - t) * a.x + t * b.x;
	float y = (1 - t) * a.y + t * b.y;
	return Vec2{ x,y };
}

inline Vec2 cubic_bezier(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, float t)
{
	Vec2 a = lerp(p0, p1, t);
	Vec2 b = lerp(p1, p2, t);
	Vec2 c = lerp(p2, p3, t);
	Vec2 d = lerp(a, b, t);
	Vec2 e = lerp(b, c, t);
	Vec2 point = lerp(d, e, t);
	return point;
}


//inline Vec2 lerp(Vec2 a, Vec2 b, float t)
//{
//	float x = a.x + t * (b.x - a.x);
//	float y = a.y + t * (b.y - a.y);
//	return Vec2
//}

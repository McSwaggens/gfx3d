#pragma once

struct Vector final
{
	float x;
	float y;
	float z;
	float w;

	Vector( const float& _x,
			const float& _y,
			const float& _z = 0.0f,
			const float& _w = 0.0f)
		: x(_x), y(_y), z(_z), w(_w) { }

	Vector(const float& xyz)
		: x(xyz), y(xyz), z(xyz), w(0.0f) { }

	constexpr Vector(
			const float&& _x,
			const float&& _y,
			const float&& _z = 0.0f,
			const float&& _w = 0.0f)
		: x(_x), y(_y), z(_z), w(_w) { }

	constexpr Vector(const float&& xyz = 0.0f)
		: x(xyz), y(xyz), z(xyz), w(0.0f) { }

	static const Vector zero;
};

constexpr const Vector Vector::zero = Vector();

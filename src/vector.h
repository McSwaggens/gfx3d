#pragma once

struct Vector final
{
	float x;
	float y;
	float z;
	float w;

	Vector(float& _x, float& _y, float& _z, float& _w)		: x(_x		), y(_y		), z(_z		), w(_w		)	{ }
	Vector(float& _x, float& _y, float& _z)					: x(_x		), y(_y		), z(_z		), w(1.0f	)	{ }
	Vector(float& _x, float& _y)							: x(_x		), y(_y		), z(0.0f	), w(1.0f	)	{ }
	Vector(float& xyz)										: x(xyz		), y(xyz	), z(xyz	), w(1.0f	)	{ }

	Vector(float&& _x, float&& _y, float&& _z, float&& _w)	: x(_x		), y(_y		), z(_z		), w(_w		)	{ }
	Vector(float&& _x, float&& _y, float&& _z)				: x(_x		), y(_y		), z(_z		), w(1.0f	)	{ }
	Vector(float&& _x, float&& _y)							: x(_x		), y(_y		), z(0.0f	), w(1.0f	)	{ }
	Vector(float&& xyz)										: x(xyz		), y(xyz	), z(xyz	), w(1.0f	)	{ }

	Vector(Vector& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
};

#pragma once

#include "Vector.h"
#include <cmath>
#include <iostream>

struct Quaternion final
{
	double r = 0;
	double i = 0;
	double j = 0;
	double k = 0;

	Quaternion Conjugate() const
	{
		return { r, -i, -j, -k };
	}

	friend Quaternion operator * (const Quaternion& a, const Quaternion& b);
	static Quaternion CreateRotation(double angle, double i, double j, double k);
	friend std::ostream& operator << (std::ostream& os, const Quaternion& z);
};


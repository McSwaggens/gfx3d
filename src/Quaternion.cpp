#include "Quaternion.h"
#include <iomanip>

Quaternion operator * (const Quaternion& a, const Quaternion& b)
{
	return
	{
		a.r*b.r - a.i*b.i - a.j*b.j - a.k*b.k,
		a.r*b.i + a.i*b.r + a.j*b.k - a.k*b.j,
		a.r*b.j + a.j*b.r + a.k*b.i - a.i*b.k,
		a.r*b.k + a.k*b.r + a.i*b.j - a.j*b.i
	};
}

Quaternion Quaternion::CreateRotation(double angle, double i, double j, double k)
{
	return
	{
		cos(angle/2),
		sin(angle/2) * i,
		sin(angle/2) * j,
		sin(angle/2) * k
	};
}

std::ostream& operator << (std::ostream& os, const Quaternion& z)
{
	os << std::fixed << std::setprecision(4)
		<< "("
		<< z.r << ", "
		<< z.i << "i, "
		<< z.j << "j, "
		<< z.k << "k)";

	return os;
}


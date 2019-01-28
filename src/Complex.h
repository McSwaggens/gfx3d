#pragma once

#include <iostream>
#include <cmath>

struct Complex final
{
	double m_r; // Real component
	double m_i; // Imaginary component

	Complex(double r, double i)
		: m_r(r), m_i(i) { }

	/*
	 * Returns a Complex number on the unit circle with a given angle in radians.
	 */
	static Complex FromRadians(double rad)
	{
		return
		{
			cos(rad),
			sin(rad)
		};
	}

	/*
	 * Returns the Complex Conjugate.
	 * This amounts to flipping the imaginary axis.
	 */
	Complex Conjugate() const
	{
		return
		{
			m_r,
			-m_i
		};
	}

	/*
	 * Returns the square magnitude of the Complex number.
	 */
	double SqrMagnitude() const
	{
		return m_r * m_r + m_i * m_i;
	}

	/*
	 * Returns the Magnitude (or length) of the Complex number.
	 */
	double Magnitude() const
	{
		return sqrt(SqrMagnitude());
	}

	/*
	 * Returns a Complex numbers on the unit circle.
	 */
	Complex Normal() const
	{
		double m = Magnitude();
		return
		{
			m_r / m,
			m_i / m
		};
	}

	/*
	 * Returns the Complex number squared.
	 */
	Complex Square() const
	{
		return
		{
			m_r * m_r - m_i * m_i,
			2 * m_r * m_i
		};
	}

	/*
	 * Performs Complex multiplication.
	 * This is NOT the same as Vector multiplication.
	 */
	Complex operator * (const Complex& z) const
	{
		return
		{
			m_r * z.m_r - m_i * z.m_i,
			m_r * z.m_i + m_i * z.m_r
		};
	}

	/*
	 * Adds two complex numbers together,
	 * this is the same as Vector addition.
	 */
	Complex operator + (const Complex z) const
	{
		return
		{
			m_r + z.m_r,
			m_i + z.m_i
		};
	}

	/*
	 * Subtracts two complex numbers,
	 * this is the same as Vector subtraction.
	 */
	Complex operator - (const Complex z) const
	{
		return
		{
			m_r - z.m_r,
			m_i - z.m_i
		};
	}

	friend std::ostream& operator << (std::ostream& os, const Complex& c)
	{
		if (c.m_i == 0)
		{
			os << c.m_r;
		}
		else if (c.m_r == 0)
		{
			os << c.m_i << "i";
		}
		else
		{
			os << "(" << c.m_r << (c.m_i < 0 ? "" : "+") << c.m_i << "i)";
		}
		return os;
	}
};

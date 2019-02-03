#pragma once

#include "Vector.h"
#include <iostream>
#include <iomanip>

/*
 * M = Rows
 * N = Columns
 */

template<size_t N, size_t M>
struct Matrix final
{
	float a[M * N];

	Matrix<N, M> operator * (const Matrix<N, M>& z) const
	{
		Matrix w = { 0 };
		for (size_t m = 0; m < M; m++)
		{
			for (size_t n = 0; n < N; n++)
			{
				for (size_t l = 0; l < M && l < N; l++)
				{
					w.a[m * M + n] += a[m * M + l] * z.a[l * M + n];
				}
			}
		}
		return w;
	}

	Vector operator * (const Vector& v) const
	{
		Vector w;
		for (size_t m = 0; m < M && m < 4; m++)
		{
			for (size_t l = 0; l < N && l < 4; l++)
			{
				w.a[m] += a[m * M + l] * v.a[l];
			}
		}
		return w;
	}

	friend std::ostream& operator << (std::ostream& os, const Matrix& x)
	{
		static const char g_dimension_symbols[] = "XYZW";
		os << std::fixed << std::setprecision(2);

		for (size_t n = 0; n < N && n < 4; n++)
		{
			os << "\t" << g_dimension_symbols[n] << ":";
		}
		os << std::endl;

		for (size_t m = 0; m < M && m < 4; m++)
		{
			os << "    " << g_dimension_symbols[m] << ": ";
			for (size_t n = 0; n < N && n < 4; n++)
			{
				os << "\t" << x.a[m * M + n];
			}
			os << std::endl;
		}
		os << std::endl;
		return os;
	}
};

void MatrixTests();


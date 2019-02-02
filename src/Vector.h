#pragma once

#include <xmmintrin.h> // SSE     - 4 float
#include <pmmintrin.h> // SSE 3   - Horizontal instructions
#include <tmmintrin.h> // SSSE 3  - Additional instructions
#include <smmintrin.h> // SSE 4.1 - Dot product
#include <nmmintrin.h> // SSE 4.2 - Additional instructions
#include <immintrin.h> // AVX     - 8 float & 4 double

struct alignas(16) Vector final
{
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		float a[4];

		__m128 mf;
	};

	constexpr
	Vector( float fx,
			float fy,
			float fz = 0.0f,
			float fw = 0.0f)
		: x(fx), y(fy), z(fz), w(fw) { }

	constexpr
	Vector(const __m128& omf) : mf(omf) { }

	constexpr
	Vector(float f) : x(f), y(f), z(f), w(f) { }

	constexpr
	Vector() : Vector(0.0f) { }

	static const Vector right;
	static const Vector left;
	static const Vector up;
	static const Vector down;
	static const Vector forward;
	static const Vector backward;

	// constexpr
	// operator __m128() const
	// {
	//     return mf;
	// }

	constexpr
	Vector& operator = (const Vector& rhs)
	{
		mf = rhs.mf;
		return *this;
	}

	// Math Operators

	inline
	Vector operator + (const Vector& rhs) const
	{
		return _mm_add_ps(mf, rhs.mf);
	}

	inline
	Vector operator + (float f) const
	{
		return _mm_add_ps(mf, _mm_set1_ps(f));
	}

	inline
	Vector operator - (const Vector& rhs) const
	{
		return _mm_sub_ps(mf, rhs.mf);
	}

	inline
	Vector operator - (float f) const
	{
		return _mm_sub_ps(mf, _mm_set1_ps(f));
	}

	inline
	Vector operator * (const Vector& rhs) const
	{
		return _mm_mul_ps(mf, rhs.mf);
	}

	inline
	Vector operator * (float f) const
	{
		return _mm_mul_ps(mf, _mm_set1_ps(f));
	}

	inline
	Vector operator / (const Vector& rhs) const
	{
		return _mm_div_ps(mf, rhs.mf);
	}

	inline
	Vector operator / (float f) const
	{
		return _mm_div_ps(mf, _mm_set1_ps(f));
	}


	// Math Functions
	
	Vector Square() const
	{
		return _mm_mul_ps(mf, mf);
	}

	float Dot4D(const Vector& v)
	{
		return _mm_cvtss_f32(_mm_dp_ps(mf, v.mf, 0xFF));
	}

	float Dot3D(const Vector& v)
	{
		return _mm_cvtss_f32(_mm_dp_ps(mf, v.mf, 0b0111'0001));
	}

	float Dot2D(const Vector& v)
	{
		return _mm_cvtss_f32(_mm_dp_ps(mf, v.mf, 0b0011'0001));
	}


};


constexpr const Vector Vector::right	= Vector(  1.0f,  0.0f,  0.0f, 0.0f );
constexpr const Vector Vector::left		= Vector( -1.0f,  0.0f,  0.0f, 0.0f );
constexpr const Vector Vector::up		= Vector(  0.0f,  1.0f,  0.0f, 0.0f );
constexpr const Vector Vector::down		= Vector(  0.0f, -1.0f,  0.0f, 0.0f );
constexpr const Vector Vector::forward	= Vector(  0.0f,  0.0f,  1.0f, 0.0f );
constexpr const Vector Vector::backward	= Vector(  0.0f,  0.0f, -1.0f, 0.0f );



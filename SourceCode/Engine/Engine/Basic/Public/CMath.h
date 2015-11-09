// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CMATH_H
#define CMATH_H

#include <Public\Common.h>
#include <math.h>

BEGIN_NAMESPACE

#define ROUNDING_ERROR 0.000001f

class BASIC_API Math
{
public:
	template<class T> static INLINE T Min(const T &A, const T &B)
	{
		return (A < B ? A : B);
	}
	template<class T> static INLINE T Max(const T &A, const T &B)
	{
		return (A < B ? B : A);
	}

	template<class T> static INLINE T Clamp(const T &Value, const T &Min, const T &Max)
	{
		return (Value < Min ? Min : (Value > Max ? Max : Value));
	}

	template<class T> static INLINE T SquareRoot(const T &Value)
	{
		return (T)sqrtf(Value);
	}

	static INLINE float32 Reciprocal(float32 Value)
	{
		return 1.0F / Value;
	}

	static INLINE bool EqualCheck(float32 A, float32 B)
	{
		return (A + ROUNDING_ERROR >= B) && (A - ROUNDING_ERROR <= B);
	}

	static INLINE bool IsZero(float32 Value)
	{
		return (Value < 0 ? -Value : Value) <= ROUNDING_ERROR;
	}

	static INLINE float32 Sin(float32 Degree)
	{
		return sin(Degree * DEGREES_TO_RADIANS);
	}

	static INLINE float32 Cos(float32 Degree)
	{
		return cos(Degree * DEGREES_TO_RADIANS);
	}

	static INLINE float32 Tan(float32 Degree)
	{
		return tan(Degree * DEGREES_TO_RADIANS);
	}

	static INLINE float32 Cot(float32 Degree)
	{
		return Cos(Degree) / Sin(Degree);
	}

public:
	static const float32 Math::DEGREES_TO_RADIANS;
	static const float32 Math::RADIANS_TO_DEGREES;
};

#undef ROUNDING_ERROR

END_NAMESPACE
#endif // CMATH_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VECTOR2_H
#define VECTOR2_H

#include <Public\Common.h>

BEGIN_NAMESPACE

struct Vector3;

//<Description>
//This is sample description
struct BASIC_API Vector2
{
public:
	INLINE Vector2(void) :
		X(0.F),
		Y(0.F)
	{
	}
	INLINE Vector2(float32 Scalar) :
		X(Scalar),
		Y(Scalar)
	{
	}
	INLINE Vector2(float32 X, float32 Y) :
		X(X),
		Y(Y)
	{
	}
	INLINE Vector2(const Vector2 &Vector) :
		X(Vector.X),
		Y(Vector.Y)
	{
	}
	Vector2(const Vector3 &Vector);

	INLINE bool operator == (const Vector2 &Vector) const
	{
		return (X == Vector.X && Y == Vector.Y);
	}
	INLINE bool operator != (const Vector2 &Vector) const
	{
		return !(X == Vector.X && Y == Vector.Y);
	}
	INLINE bool operator <= (const Vector2 &Vector) const
	{
		return (X <= Vector.X || Y <= Vector.Y);
	}
	INLINE bool operator >= (const Vector2 &Vector) const
	{
		return (X >= Vector.X || Y >= Vector.Y);
	}
	INLINE bool operator < (const Vector2 &Vector) const
	{
		return (X < Vector.X || Y < Vector.Y);
	}
	INLINE bool operator > (const Vector2 &Vector) const
	{
		return (X > Vector.X || Y > Vector.Y);
	}

	INLINE Vector2 &operator = (float32 Scalar)
	{
		X = Y = Scalar;

		return *this;
	}
	INLINE Vector2 &operator = (const Vector2 &Vector)
	{
		X = Vector.X;
		Y = Vector.Y;

		return *this;
	}
	Vector2 &operator = (const Vector3 &Vector);

	INLINE Vector2 operator + (const Vector2 &Vector) const
	{
		return Vector2(X + Vector.X, Y + Vector.Y);
	}
	INLINE Vector2 &operator += (const Vector2 &Vector)
	{
		X += Vector.X;
		Y += Vector.Y;

		return *this;
	}

	INLINE Vector2 operator - (const Vector2 &Vector) const
	{
		return Vector2(X - Vector.X, Y - Vector.Y);
	}
	INLINE Vector2 &operator -= (const Vector2 &Vector)
	{
		X -= Vector.X;
		Y -= Vector.Y;

		return *this;
	}

	INLINE Vector2 operator * (float32 Value) const
	{
		return Vector2(X * Value, Y * Value);
	}
	INLINE Vector2 operator * (const Vector2 &Vector) const
	{
		return Vector2(X * Vector.X, Y * Vector.Y);
	}
	INLINE Vector2 &operator *= (float32 Value)
	{
		X *= Value;
		Y *= Value;

		return *this;
	}
	INLINE Vector2 &operator *= (const Vector2 &Vector)
	{
		X *= Vector.X;
		Y *= Vector.Y;

		return *this;
	}

	INLINE Vector2 operator / (float32 Value) const
	{
		return Vector2(X / Value, Y / Value);
	}
	INLINE Vector2 operator / (const Vector2 &Vector) const
	{
		return Vector2(X / Vector.X, Y / Vector.Y);
	}
	INLINE Vector2 &operator /= (float32 Value)
	{
		X /= Value;
		Y /= Value;

		return *this;
	}
	INLINE Vector2 &operator /= (const Vector2 &Vector)
	{
		X /= Vector.X;
		Y /= Vector.Y;

		return *this;
	}

public:
	float32 X, Y;

	static const Vector2 ZERO;
	static const Vector2 ONE;
	static const Vector2 UNIT_X;
	static const Vector2 UNIT_Y;
};

END_NAMESPACE
#endif // VECTOR2_H

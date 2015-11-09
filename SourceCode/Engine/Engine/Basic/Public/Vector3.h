// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VECTOR3_H
#define VECTOR3_H

#include <Public\Common.h>
#include <math.h>

BEGIN_NAMESPACE

struct Vector2;

//<Description>
//This is sample description
struct BASIC_API Vector3
{
public:
	INLINE Vector3(void) :
		X(0.F),
		Y(0.F),
		Z(0.F)
	{
	}
	INLINE Vector3(float32 Scalar) :
		X(Scalar),
		Y(Scalar),
		Z(Scalar)
	{
	}
	INLINE Vector3(float32 X, float32 Y, float32 Z) :
		X(X),
		Y(Y),
		Z(Z)
	{
	}
	INLINE Vector3(const Vector3 &Vector) :
		X(Vector.X),
		Y(Vector.Y),
		Z(Vector.Z)
	{
	}
	Vector3(const Vector2 &Vector);
	Vector3(const Vector2 &Vector, float32 Z);

	INLINE bool operator == (const Vector3 &Vector) const
	{
		return (X == Vector.X && Y == Vector.Y && Z == Vector.Z);
	}
	INLINE bool operator != (const Vector3 &Vector) const
	{
		return !(X == Vector.X && Y == Vector.Y && Z == Vector.Z);
	}
	INLINE bool operator <= (const Vector3 &Vector) const
	{
		return (X <= Vector.X || Y <= Vector.Y || Z <= Vector.Z);
	}
	INLINE bool operator >= (const Vector3 &Vector) const
	{
		return (X >= Vector.X || Y >= Vector.Y || Z >= Vector.Z);
	}
	INLINE bool operator < (const Vector3 &Vector) const
	{
		return (X < Vector.X || Y < Vector.Y || Z < Vector.Z);
	}
	INLINE bool operator >(const Vector3 &Vector) const
	{
		return (X > Vector.X || Y > Vector.Y || Z > Vector.Z);
	}

	INLINE Vector3 &operator = (float32 Scalar)
	{
		X = Y = Z = Scalar;

		return *this;
	}
	INLINE Vector3 &operator = (const Vector3 &Vector)
	{
		X = Vector.X;
		Y = Vector.Y;
		Z = Vector.Z;

		return *this;
	}
	Vector3 &operator = (const Vector2 &Vector);

	INLINE Vector3 operator + (const Vector3 &Vector) const
	{
		return Vector3(X + Vector.X, Y + Vector.Y, Z + Vector.Z);
	}
	INLINE Vector3 &operator += (const Vector3 &Vector)
	{
		X += Vector.X;
		Y += Vector.Y;
		Z += Vector.Z;

		return *this;
	}

	INLINE Vector3 operator - (const Vector3 &Vector) const
	{
		return Vector3(X - Vector.X, Y - Vector.Y, Z - Vector.Z);
	}
	INLINE Vector3 &operator -= (const Vector3 &Vector)
	{
		X -= Vector.X;
		Y -= Vector.Y;
		Z -= Vector.Z;

		return *this;
	}
	
	INLINE Vector3 operator * (float32 Value) const
	{
		return Vector3(X * Value, Y * Value, Z * Value);
	}
	INLINE Vector3 operator * (const Vector3 &Vector) const
	{
		return Vector3(X * Vector.X, Y * Vector.Y, Z * Vector.Z);
	}
	INLINE Vector3 &operator *= (float32 Value)
	{
		X *= Value;
		Y *= Value;
		Z *= Value;

		return *this;
	}
	INLINE Vector3 &operator *= (const Vector3 &Vector)
	{
		X *= Vector.X;
		Y *= Vector.Y;
		Z *= Vector.Z;

		return *this;
	}
	
	INLINE Vector3 operator / (float32 Value) const
	{
		return Vector3(X / Value, Y / Value, Z / Value);
	}
	INLINE Vector3 operator / (const Vector3 &Vector) const
	{
		return Vector3(X / Vector.X, Y / Vector.Y, Z / Vector.Z);
	}
	INLINE Vector3 &operator /= (float32 Value)
	{
		X /= Value;
		Y /= Value;
		Z /= Value;

		return *this;
	}
	INLINE Vector3 &operator /= (const Vector3 &Vector)
	{
		X /= Vector.X;
		Y /= Vector.Y;
		Z /= Vector.Z;

		return *this;
	}

	INLINE const float32 Length(void) const
	{
		return sqrt(LengthSqr());
	}
	INLINE const float32 LengthSqr(void) const
	{
		return X * X + Y * Y + Z * Z;
	}

	INLINE void Normalize(void)
	{
		const float32 length = Length();
		X /= length;
		Y /= length;
		Z /= length;
	}
	INLINE Vector3 Normalized(void) const
	{
		Vector3 Vector(*this);
		Vector.Normalize();
		return Vector;
	}

	INLINE float32 DistanceTo(const Vector3 &Vector) const
	{
		return (Vector - *this).Length();
	}

	INLINE float32 DotProduct(const Vector3 &Vector) const
	{
		return X * Vector.X + Y * Vector.Y + Z * Vector.Z;
	}

	INLINE Vector3 CrossProduct(const Vector3 &Vector) const
	{
		return Vector3(Y * Vector.Z - Z * Vector.Y, Z * Vector.X - X * Vector.Z, X * Vector.Y - Y * Vector.X);
	}

	INLINE float32 AngleBetween(const Vector3 &Vector) const
	{
		return acos(Normalized().DotProduct(Vector.Normalized()));
	}

public:
	float32 X, Y, Z;

	static const Vector3 ZERO;
	static const Vector3 ONE;
	static const Vector3 UNIT_X;
	static const Vector3 UNIT_Y;
	static const Vector3 UNIT_Z;
};

END_NAMESPACE
#endif // VECTOR3_H

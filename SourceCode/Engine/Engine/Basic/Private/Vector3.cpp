// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Vector3.h>
#include <Public\Vector2.h>


BEGIN_NAMESPACE


const Vector3 Vector3::ZERO(0);
const Vector3 Vector3::ONE(1);
const Vector3 Vector3::UNIT_X(1, 0, 0);
const Vector3 Vector3::UNIT_Y(0, 1, 0);
const Vector3 Vector3::UNIT_Z(0, 0, 1);


Vector3::Vector3(const Vector2 &Vector) :
	X(Vector.X),
	Y(Vector.Y),
	Z(0.f)
{
}


Vector3::Vector3(const Vector2 &Vector, float32 Z) :
	X(Vector.X),
	Y(Vector.Y),
	Z(Z)
{
}


Vector3 &Vector3::operator = (const Vector2 &Vector)
{
	X = Vector.X;
	Y = Vector.Y;

	return *this;
}

END_NAMESPACE

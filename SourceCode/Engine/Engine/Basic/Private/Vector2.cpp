// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Vector2.h>
#include <Public\Vector3.h>

BEGIN_NAMESPACE

const Vector2 Vector2::ZERO(0);
const Vector2 Vector2::ONE(1);
const Vector2 Vector2::UNIT_X(1, 0);
const Vector2 Vector2::UNIT_Y(0, 1);


Vector2::Vector2(const Vector3 &Vector) :
X(Vector.X),
Y(Vector.Y)
{
}


Vector2 &Vector2::operator = (const Vector3 &Vector)
{
	X = Vector.X;
	Y = Vector.Y;

	return *this;
}

END_NAMESPACE

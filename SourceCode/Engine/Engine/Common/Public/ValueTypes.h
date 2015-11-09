// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VALUETYPES_H
#define VALUETYPES_H

#include <Public\SecondaryCommon.h>

BEGIN_NAMESPACE

enum class ValueTypes
{
	None = 0,

	Void,

	Bool,

	UInt8,
	UInt16,
	UInt32,
	UInt64,

	Int8,
	Int16,
	Int32,
	Int64,

	Float32,
	Float64,

	Double32,
	Double64,

	String,
	Vector2,
	Vector3,
	Matrix4
};


END_NAMESPACE
#endif // VALUETYPES_H

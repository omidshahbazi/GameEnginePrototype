// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IBOXSHAPE_H
#define IBOXSHAPE_H

#include <Public\IShape.h>

BEGIN_NAMESPACE

class IBoxShape : public IShape
{
public:
	virtual ~IBoxShape(void) {}

	virtual void SetCenter(const Vector2 &Center) = 0;
	virtual const Vector2 &GetCenter(void) const = 0;

	virtual void SetHalfSize(const Vector2 &HalfSize) = 0;
	virtual const Vector2 &GetHalfSize(void) const = 0;

};

END_NAMESPACE
#endif // IBOXSHAPE_H

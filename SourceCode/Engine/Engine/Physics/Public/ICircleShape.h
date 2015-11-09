// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICIRCLESHAPE_H
#define ICIRCLESHAPE_H

#include <Public\IShape.h>

BEGIN_NAMESPACE

class ICircleShape : public IShape
{
public:
	virtual ~ICircleShape(void) {}

	virtual void SetCenter(const Vector2 &Center) = 0;
	virtual const Vector2 &GetCenter(void) const = 0;

	virtual void SetRadius(float32 Value) = 0;
	virtual float32 GetRadius(void) const = 0;

};

END_NAMESPACE
#endif // ICIRCLESHAPE_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H

#include <Public\Physics\ICircleShape.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class CircleShape : public ICircleShape
{
public:
	CircleShape(b2CircleShape *Shape);
	~CircleShape(void);

	void SetCenter(const Vector2 &Center);
	const Vector2 &GetCenter(void) const
	{
		return m_Center;
	}

	void SetRadius(float32 Value);
	float32 GetRadius(void) const
	{
		return m_Radius;
	}

private:
	b2CircleShape *m_Shape;

	float m_Radius;
	Vector2 m_Center;
};

END_NAMESPACE
#endif // CIRCLESHAPE_H

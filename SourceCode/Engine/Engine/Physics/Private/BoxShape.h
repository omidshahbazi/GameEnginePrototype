// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include <Public\Physics\IBoxShape.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class BoxShape : public IBoxShape
{
public:
	BoxShape(b2PolygonShape *Shape, const Vector2 &HalfSize);
	~BoxShape(void);

	void SetCenter(const Vector2 &Center);
	const Vector2 &GetCenter(void) const
	{
		return m_Center;
	}

	void SetHalfSize(const Vector2 &HalfSize);
	const Vector2 &GetHalfSize(void) const
	{
		return m_HalfSize;
	}

private:
	b2PolygonShape *m_Shape;

	Vector2 m_Center;
	Vector2 m_HalfSize;
};

END_NAMESPACE
#endif // BOXSHAPE_H

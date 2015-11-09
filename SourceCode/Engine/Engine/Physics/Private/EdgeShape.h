// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef EDGESHAPE_H
#define EDGESHAPE_H

#include <Public\Physics\IEdgeShape.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class EdgeShape : public IEdgeShape
{
public:
	EdgeShape(b2EdgeShape *Shape);
	~EdgeShape(void);

	void SetBeginPoint(const Vector2 &Point);
	const Vector2 &GetBeginPoint(void) const
	{
		return m_Begin;
	}


	void SetEndPoint(const Vector2 &Point);
	const Vector2 &GetEndPoint(void) const
	{
		return m_End;
	}

private:
	b2EdgeShape *m_Shape;

	Vector2 m_Begin;
	Vector2 m_End;
};

END_NAMESPACE
#endif // EDGESHAPE_H

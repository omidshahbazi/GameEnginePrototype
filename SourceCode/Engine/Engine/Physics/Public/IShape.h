// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ISHAPE_H
#define ISHAPE_H

#include <Public\Vector2.h>

BEGIN_NAMESPACE

class IShape
{
public:
	enum class ShapeType
	{
		ST_CIRCLE = 0,
		ST_BOX,
		ST_POLYGON,
		ST_EDGE
	};

public:
	virtual ~IShape(void) {}

	const ShapeType &GetType(void) const
	{
		return m_Type;
	}

protected:
	ShapeType m_Type;
};

END_NAMESPACE
#endif // ISHAPE_H

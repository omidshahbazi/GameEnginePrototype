// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include <Public\Vector3.h>

BEGIN_NAMESPACE

struct Line3D;

struct BASIC_API BoundingSphere
{
public:
	BoundingSphere(void);
	
	void Reset(void);

	void InsertPoint(const Vector3 &Point);

	float32 GetRadius(void) const
	{
		return m_Radius;
	}
	
	bool IntersectsWithLine(const Line3D &Line) const;

private:
	float m_Radius;
};

END_NAMESPACE

#endif // BOUNDINGSPHERE_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef LINE3D_H
#define LINE3D_H

#include <Public\Vector3.h>

BEGIN_NAMESPACE


struct BASIC_API Line3D
{
public:
	Line3D(void);
	Line3D(const Vector3 &Start, const Vector3 &End);

	~Line3D(void);

	const Vector3 &GetStart(void) const
	{
		return m_Start;
	}

	const Vector3 &GetEnd(void) const
	{
		return m_End;
	}
 
	float32 GetLength(void) const
	{
		return m_Start.DistanceTo(m_End);
	}

	Vector3 GetMiddle(void) const
	{
		return (m_Start + m_End) / 2;
	}

	Vector3 GetDirection(void) const
	{
		return m_End - m_Start;
	}
public:
	Vector3 m_Start;
	Vector3 m_End;

};


END_NAMESPACE
#endif // LINE3D_H

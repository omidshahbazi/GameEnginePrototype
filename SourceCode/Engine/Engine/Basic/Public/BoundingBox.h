// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <Public\Vector3.h>

BEGIN_NAMESPACE

struct Line3D;

struct BASIC_API BoundingBox
{
public:
	BoundingBox(void);
	
	void Reset(void);

	void InsertPoint(const Vector3 &Point);

	float32 GetInnerRadius(void) const;
	float32 GetOuterRadius(void) const;
	
	INLINE const Vector3 &GetLowerCorner(void) const
	{
		return m_LowerCorner;
	}
	INLINE void SetLowerCorner(const Vector3 &Value)
	{
		m_LowerCorner = Value;
	}

	INLINE const Vector3 &GetUpperCorner(void) const
	{
		return m_UpperCorner;
	}
	INLINE void SetUpperCorner(const Vector3 &Value)
	{
		m_UpperCorner = Value;
	}

	INLINE Vector3 GetExtents(void) const
	{
		return m_UpperCorner - m_LowerCorner;
	}
	INLINE Vector3 GetCenter(void) const
	{
		return m_LowerCorner + (GetExtents() / 2.0F);
	}
	
	bool IntersectsWithLine(const Line3D &Line) const;

private:
	Vector3 m_LowerCorner;
	Vector3 m_UpperCorner;
};

END_NAMESPACE

#endif // BOUNDINGBOX_H

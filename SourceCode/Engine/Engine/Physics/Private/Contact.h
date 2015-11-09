// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CONTACT_H
#define CONTACT_H

#include <Public\Physics\IContact.h>

BEGIN_NAMESPACE

class Contact : public IContact
{
public:
	Contact(void);
	Contact(IFixture *OtherFixture, Vector2 *Points, uint32 PointCount);
	~Contact(void) {}


	IFixture *GetOtherFixture(void)
	{
		return m_OtherFixture;
	}


	const Vector2 *GetPoints(void)
	{
		return m_Points;
	}


	uint32 GetPointCount(void)
	{
		return m_PointCount;
	}


private:
	unsigned int m_PointCount;

	Vector2 *m_Points;

	IFixture *m_OtherFixture;

};

END_NAMESPACE
#endif // CONTACT_H

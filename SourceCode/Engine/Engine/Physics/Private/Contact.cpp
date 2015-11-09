// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Contact.h>


BEGIN_NAMESPACE


Contact::Contact(void) :
	m_OtherFixture(NULL),
	m_Points(NULL),
	m_PointCount(0)
{

}


Contact::Contact(IFixture *OtherFixture, Vector2 *Points, uint32 PointCount) :
	m_OtherFixture(OtherFixture),
	m_Points(Points),
	m_PointCount(PointCount)
{
}


END_NAMESPACE

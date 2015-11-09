// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\ContactImpulse.h>


BEGIN_NAMESPACE


ContactImpulse::ContactImpulse(float *NormalImpulse, float *TangentImpulse, uint32 ImpulseCount) :
	m_NormalImpulse(NormalImpulse),
	m_TangentImpulse(TangentImpulse),
	m_ImpulseCount(ImpulseCount)
{
}


ContactImpulse::~ContactImpulse(void)
{

}


uint32 ContactImpulse::GetImpulseCount(void)
{
	return m_ImpulseCount;
}


const float *ContactImpulse::GetNormalImpulse(void)
{
	return m_NormalImpulse;
}


const float *ContactImpulse::GetTangentImpulse(void)
{
	return m_TangentImpulse;
}


END_NAMESPACE

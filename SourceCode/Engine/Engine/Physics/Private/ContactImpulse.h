// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CONTACTIMPULSE_H
#define CONTACTIMPULSE_H

#include <Public\Physics\IContactImpulse.h>

BEGIN_NAMESPACE

class ContactImpulse : public IContactImpulse
{
public:
	ContactImpulse(float *NormalImpulse, float *TangentImpulse, uint32 ImpulseCount);
	~ContactImpulse(void);

	uint32 GetImpulseCount(void);

	const float *GetNormalImpulse(void);

	const float *GetTangentImpulse(void);

private:
	unsigned int m_ImpulseCount;

	float *m_NormalImpulse;

	float *m_TangentImpulse;

};

END_NAMESPACE
#endif // CONTACTIMPULSE_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPULLEYJOINT_H
#define IPULLEYJOINT_H

#include <Public\IJoint.h>

BEGIN_NAMESPACE

class IPulleyJoint : public IJoint
{
public:
	virtual ~IPulleyJoint(void) {}

	virtual const Vector2 GetAnchorA(void) const = 0;

	virtual const Vector2 &GetLocalAnchorA(void) const = 0;

	virtual const Vector2 GetAnchorB(void) const = 0;

	virtual const Vector2 &GetLocalAnchorB(void) const = 0;

	virtual const Vector2 &GetGroundAnchorA(void) const = 0;

	virtual const Vector2 &GetGroundAnchorB(void) const = 0;

	virtual float32 GetLengthA(void) const = 0;

	virtual float32 GetLenghtB(void) const = 0;

	virtual float32 GetRatio(void) const = 0;
};

END_NAMESPACE
#endif // IPULLEYJOINT_H

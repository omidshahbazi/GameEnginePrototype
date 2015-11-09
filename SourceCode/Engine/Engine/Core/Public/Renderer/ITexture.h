// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ITEXTURE_H
#define ITEXTURE_H

#include <Public\Resource.h>

BEGIN_NAMESPACE

struct Vector2;

class ITexture : public Resource
{
public:
	virtual ~ITexture(void) {}

	virtual const Vector2 &GetSize(void) const = 0;
};

END_NAMESPACE
#endif // ITEXTURE_H

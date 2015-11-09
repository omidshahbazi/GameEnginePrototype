// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IFONT_H
#define IFONT_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class IFont
{
public:
	virtual ~IFont(void) {}

	virtual const String &GetName(void) const = 0;

	virtual void SetSize(uint32 Size) = 0;
	virtual uint32 GetSize(void) const = 0;
	
	virtual void SetNewLineRatio(float32 Ratio) = 0;
	virtual float32 GetNewLineRatio(void) const = 0;
};

END_NAMESPACE
#endif // IFONT_H

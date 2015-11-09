// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ILABEL_H
#define ILABEL_H

#include <Public\IGUIObject.h>

BEGIN_NAMESPACE

class ILabel : public IGUIObject
{
public:
	virtual ~ILabel(void) {}
	
	virtual void SetOffset(const Vector2 &Offset) = 0;
	virtual const Vector2 &GetOffset(void) = 0;

	virtual void SetText(const String &Text) = 0;
	virtual const String &GetText(void) = 0;
};

END_NAMESPACE
#endif // ILABEL_H

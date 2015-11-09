// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPROGRESSBAR_H
#define IPROGRESSBAR_H

#include <Public\IGUIObject.h>

BEGIN_NAMESPACE

class IProgressBar : public IGUIObject
{
public:
	virtual ~IProgressBar(void) {}
	
	virtual void SetPrecent(float32 Precent) = 0;

	virtual void SetBarColour(const Colour &Colour) = 0;
	virtual const Colour &GetBarColour(void) = 0;

	virtual void SetBarImage(Image *Image) = 0;
	virtual Image *GetBarImage(void) = 0;

	virtual void SetDisplayText(bool DisplayText) = 0;
	virtual bool GetDisplayText(void) = 0;
};

END_NAMESPACE
#endif // IPROGRESSBAR_H

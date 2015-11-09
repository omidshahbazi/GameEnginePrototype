// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMOVIE_H
#define IMOVIE_H

#include <Public\Renderer\ITexture.h>
#include <Public\Vector2.h>

BEGIN_NAMESPACE

//<Description>
//This is sample description
class IMovie
{
public:
	virtual ~IMovie(void) {}

	virtual void Update(void) = 0;

	virtual void Play(void) = 0;
	virtual void Pause(void) = 0;
	virtual void Stop(void) = 0;

	virtual void SetFPS(uint32 FPS) = 0;

	virtual ITexture *GetTexture(void) = 0;

	virtual const Vector2 &GetSize(void) = 0;

	virtual float32 GetDuration(void) = 0;
	
	virtual void SetLoop(bool Value) = 0;
	virtual bool GetLoop(void) const = 0;
};

END_NAMESPACE
#endif // IMOVIE_H

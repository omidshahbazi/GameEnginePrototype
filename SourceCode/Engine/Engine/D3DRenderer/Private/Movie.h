// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MOVIE_H
#define MOVIE_H

#include <Public\Renderer\IRenderEngine.h>
#include <Public\Renderer\IMovie.h>
#include <Private\Texture.h>
#include <dshow.h>
#include <mmstream.h>
#include <amstream.h>
#include <ddstream.h>

BEGIN_NAMESPACE

class Movie : public IMovie
{
public:
	Movie(const String &RelativeFilePath);
	~Movie(void);

	void Update(void);

	void Play(void);
	void Pause(void);
	void Stop(void);

	void SetFPS(uint32 FPS)
	{
		m_FPS = FPS;
	}

	ITexture *GetTexture(void)
	{
		return m_Texture;
	}

	const Vector2 &GetSize(void)
	{
		return m_Size;
	}

	float32 GetDuration(void)
	{
		return m_Duration;
	}

	void SetLoop(bool Value)
	{
		m_Loop = Value;
	}
	bool GetLoop(void) const
	{
		return m_Loop;
	}

private:
	IAMMultiMediaStream *m_MediaStream;
    IMediaStream *m_VideoStream;
    IDirectDrawMediaStream *m_DrawStream;
    IDirectDrawStreamSample *m_Sample;
    IDirectDrawSurface *m_Surface;

    uint32 m_FPS;

    uint32 m_LastUpdateTime;

	IRenderEngine *m_Engine;
	Texture *m_Texture;
	Vector2 m_Size;
	float32 m_Duration;
	bool m_Loop;
	float32 m_StartTime;
};

END_NAMESPACE
#endif // MOVIE_H

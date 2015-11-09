// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FRAMESTATS_H
#define FRAMESTATS_H
#include <Public\Common.h>

BEGIN_NAMESPACE

class FrameStats
{
public:
	FrameStats(void) :
		TargetFPS(0),
		TargetFrameTime(0.0F),
		FPS(0),
		AverageFrameTime(0.0F)
	{
	}

public:
	uint16 TargetFPS;
	float32 TargetFrameTime;
	uint16 FPS;
	float32 AverageFrameTime;
};

END_NAMESPACE
#endif // FRAMESTATS_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GPUPARAMDEFINITION_H
#define GPUPARAMDEFINITION_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class CORE_API GPUParamDefinition
{
public:
	static const String WORLD_MATRIX;
	static const String VIEW_MATRIX;
	static const String PROJECTION_MATRIX;
	static const String WORLDVIEWPROJECTION_MATRIX;

	static const String TIME;
	static const String REAL_TIME;

	static const String NEAR_CLIP_DISTANCE;
	static const String FAR_CLIP_DISTANCE;

	static const String TARGET_SIZE;
	static const String ASPECT_RATIO;
};

END_NAMESPACE
#endif // GPUPARAMDEFINITION_H

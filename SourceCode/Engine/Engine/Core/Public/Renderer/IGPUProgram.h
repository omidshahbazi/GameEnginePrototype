// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGPUPROGRAM_H
#define IGPUPROGRAM_H

#include <Public\Resource.h>
#include <Public\Map.h>
#include <Public\ReflectionDefinitions.h>

BEGIN_NAMESPACE

REFLECTION_ENUM()
enum class VertexShaderTypes
{
	v1_1 = 0,
	v2,
	v2a,
	v3,
	v4,
	v4_1,
	v5
};

REFLECTION_ENUM()
enum class FragmentShaderTypes
{
	v1_1 = 0,
	v1_2,
	v1_3,
	v1_4,
	v2,
	v2a,
	v2b,
	v3,
	v4,
	v4_1,
	v5
};

class IGPUProgram : public Resource
{
public:
	typedef Map<String, String> DefinesMap;

public:
	virtual ~IGPUProgram(void) {}

	virtual bool HasError(void) const = 0;
};

END_NAMESPACE
#endif // IGPUPROGRAM_H

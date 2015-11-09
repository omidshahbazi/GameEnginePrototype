// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICOMPOSITEPASS_H
#define ICOMPOSITEPASS_H
#include <Public\Renderer\IGPUProgramUsage.h>
#include <Public\Renderer\IRenderTarget.h>

BEGIN_NAMESPACE

struct Colour;

enum class CompositeInputTypes
{
	None = 0,
	Scene,
	Previous,
	RenderTarget
};

class ICompositePass
{
public:
	struct InputStage
	{
	public:
		CompositeInputTypes InputType;
		ITexture *Texture;
	};

public:
	virtual ~ICompositePass(void) {}

	virtual InputStage &GetInputStage(uint8 Stage) = 0;

	virtual IRenderTarget *GetTarget(void) = 0;
	virtual void SetTarget(IRenderTarget *RenderTarget) = 0;

	virtual const Colour &GetClearColour(void) const = 0;
	virtual void SetClearColour(const Colour &Colour) = 0;

	virtual void SetProgram(IGPUProgram *Program) = 0;
	virtual IGPUProgramUsage *GetProgram(void) = 0;
};

END_NAMESPACE
#endif // ICOMPOSITEPASS_H

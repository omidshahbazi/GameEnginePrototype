// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPOSITEPASS_H
#define COMPOSITEPASS_H
#include <Public\Renderer\ICompositePass.h>
#include <Private\GPUProgramUsage.h>
#include <Public\Colour.h>

BEGIN_NAMESPACE

class CompositePass : public ICompositePass
{
public:
	CompositePass(void);
	virtual ~CompositePass(void) {}

	InputStage &GetInputStage(uint8 Stage)
	{
		return m_InputStages[Stage];
	}

	IRenderTarget *GetTarget(void)
	{
		return m_Target;
	}
	void SetTarget(IRenderTarget *RenderTarget)
	{
		m_Target = RenderTarget;
	}

	const Colour &GetClearColour(void) const
	{
		return m_ClearColour;
	}
	void SetClearColour(const Colour &Colour)
	{
		m_ClearColour = Colour;
	}

	void SetProgram(IGPUProgram *Program)
	{
		m_Program.SetProgram(Program);
	}
	IGPUProgramUsage *GetProgram(void)
	{
		return &m_Program;
	}

private:
	typedef Vector<CompositePass*> CompositePassesList;

	InputStage *m_InputStages;
	IRenderTarget *m_Target;

	Colour m_ClearColour;

	GPUProgramUsage m_Program;
};

END_NAMESPACE
#endif // COMPOSITEPASS_H

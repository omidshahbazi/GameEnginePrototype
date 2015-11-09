// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <Public\Renderer\IComposite.h>
#include <Private\CompositePass.h>
#include <Private\RenderTargetTexture.h>

BEGIN_NAMESPACE

class Composite : public IComposite
{
public:
	virtual ~Composite(void) {}

	ICompositePass *CreatePass(void)
	{
		CompositePass *pass = new CompositePass();
		m_Passes.Add(pass);
		return pass;
	}

	ICompositePass *GetPass(uint8 Index) const
	{
		return m_Passes[Index];
	}

	const PassesList &GetPasses(void) const
	{
		return m_Passes;
	}

private:
	PassesList m_Passes;
};

END_NAMESPACE
#endif // COMPOSITE_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\CompositePass.h>
#include <Public\Core.h>
#include <Public\Renderer\IRenderEngine.h>


BEGIN_NAMESPACE


CompositePass::CompositePass(void) :
m_Target(NULL),
m_ClearColour(Colour::BLACK)
{
	static const uint8 MaxTexCount = Core::GetReference().GetRenderer()->GetMaxSupportedTexturesCount();

	m_InputStages = new InputStage[MaxTexCount];
	memset(m_InputStages, NULL, MaxTexCount * sizeof(InputStage));
}


END_NAMESPACE

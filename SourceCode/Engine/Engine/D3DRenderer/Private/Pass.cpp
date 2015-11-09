// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Pass.h>
#include <Public\Core.h>
#include <Public\Renderer\IRenderEngine.h>


BEGIN_NAMESPACE


Pass::Pass(void) :
	m_FillMode(FillModes::Solid),
	m_ZCompareFunction(CompareFunctions::Always),
	m_ZWrite(true),
	m_BlendOperation(BlendOperations::Add),
	m_SourceBlendFactor(BlendFactors::Zero),
	m_DestinationBlendFactor(BlendFactors::One),
	m_AlphaTestFunction(CompareFunctions::Always),
	m_AlphaTestReference(255),
	m_CullType(CullTypes::ClockWise)
{
	static const uint8 MaxTexCount = Core::GetReference().GetRenderer()->GetMaxSupportedTexturesCount();

	m_Textures = new TexturePointer[MaxTexCount];
	memset(m_Textures, NULL, MaxTexCount * sizeof(TexturePointer));
}


//Pass::~Pass(void)
//{
//}

END_NAMESPACE

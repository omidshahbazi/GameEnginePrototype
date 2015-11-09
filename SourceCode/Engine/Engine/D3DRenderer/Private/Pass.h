// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PASS_H
#define PASS_H

#include <Public\Renderer\IPass.h>
#include <Public\Renderer\ITexture.h>
#include <Private\GPUProgramUsage.h>

BEGIN_NAMESPACE

class Pass : public IPass
{
public:
	typedef ITexture* TexturePointer;

public:
	Pass(void);
	//~Pass(void);

	void SetFillMode(FillModes Mode)
	{
		m_FillMode = Mode;
	}
	FillModes GetFillMode(void) const
	{
		return m_FillMode;
	}

	void SetZCompareFunction(CompareFunctions Function)
	{
		m_ZCompareFunction = Function;
	}
	CompareFunctions GetZCompareFunction(void) const
	{
		return m_ZCompareFunction;
	}

	void SetZWrite(bool Value)
	{
		m_ZWrite = Value;
	}
	bool GetZWrite(void) const
	{
		return m_ZWrite;
	}

	void SetBlendOperation(BlendOperations Operation)
	{
		m_BlendOperation = Operation;
	}
	BlendOperations GetBlendOperation(void) const
	{
		return m_BlendOperation;
	}

	void SetSourceBlendFactor(BlendFactors Factor)
	{
		m_SourceBlendFactor = Factor;
	}
	BlendFactors GetSourceBlendFactor(void) const
	{
		return m_SourceBlendFactor;
	}

	void SetDestinationBlendFactor(BlendFactors Factor)
	{
		m_DestinationBlendFactor = Factor;
	}
	BlendFactors GetDestinationBlendFactor(void) const
	{
		return m_DestinationBlendFactor;
	}

	void SetAlphaTestFunction(CompareFunctions Function)
	{
		m_AlphaTestFunction = Function;
	}
	CompareFunctions GetAlphaTestFunction(void) const
	{
		return m_AlphaTestFunction;
	}

	void SetAlphaTestReference(uint8 Reference)
	{
		m_AlphaTestReference = Reference;
	}
	uint8 GetAlphaTestReference(void) const
	{
		return m_AlphaTestReference;
	}

	void SetCullType(CullTypes Mode)
	{
		m_CullType = Mode;
	}
	CullTypes GetCullType(void) const
	{
		return m_CullType;
	}

	void SetTextureStage(uint8 Stage, ITexture *Texture)
	{
		m_Textures[Stage] = Texture;
	}
	ITexture *GetTextureStage(uint8 Stage = 0) const
	{
		return m_Textures[Stage];
	}

	void SetVertexProgram(IGPUProgram *Program)
	{
		m_VertexProgram.SetProgram(Program);
	}
	IGPUProgramUsage *GetVertexProgram(void)
	{
		return &m_VertexProgram;
	}

	void SetFragmentProgram(IGPUProgram *Program)
	{
		m_FragmentProgram.SetProgram(Program);
	}
	IGPUProgramUsage *GetFragmentProgram(void)
	{
		return &m_FragmentProgram;
	}

private:
	FillModes m_FillMode;
	CompareFunctions m_ZCompareFunction;
	bool m_ZWrite;
	BlendOperations m_BlendOperation;
	BlendFactors m_SourceBlendFactor;
	BlendFactors m_DestinationBlendFactor;
	CompareFunctions m_AlphaTestFunction;
	uint8 m_AlphaTestReference;
	CullTypes m_CullType;
	TexturePointer *m_Textures;

	GPUProgramUsage m_VertexProgram;
	GPUProgramUsage m_FragmentProgram;
};

END_NAMESPACE
#endif // PASS_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IPASS_H
#define IPASS_H

#include <Public\ISerializable.h>
#include <Public\ReflectionDefinitions.h>

BEGIN_NAMESPACE

class ITexture;
class IGPUProgram;
class IGPUProgramUsage;

REFLECTION_ENUM()
enum class FillModes
{
	Point = 0,
	Wireframe,
	Solid
};

REFLECTION_ENUM()
enum class CompareFunctions
{
	Never = 0,
	Less,
	Equal,
	LessEqual,
	Greater,
	NotEqual,
	GreaterEqual,
	Always
};

REFLECTION_ENUM()
enum class BlendOperations
{
	None = 0,
	Add,
	Min,
	Max,
	Subtract,
	RevSubtract
};

REFLECTION_ENUM()
enum class BlendFactors
{
	Zero = 0,
	One,
	DestinationColour,
	OneMinusDestinationColour,
	SourceColour,
	OneMinusSourceColour,
	SourceAlpha,
	OneMinusSourceAlpha,
	DestinationAlpha,
	OneMinusDestinationAlpha,
	SourceAlphaSaturate
};

REFLECTION_ENUM()
enum class CullTypes
{
	None = 0,
	ClockWise,
	CoClockWise
};

class IPass : public ISerializable
{
public:
	virtual ~IPass(void) {}

	virtual void SetFillMode(FillModes Mode) = 0;
	virtual FillModes GetFillMode(void) const = 0;

	virtual void SetZCompareFunction(CompareFunctions Function) = 0;
	virtual CompareFunctions GetZCompareFunction(void) const = 0;

	virtual void SetZWrite(bool Value) = 0;
	virtual bool GetZWrite(void) const = 0;

	virtual void SetBlendOperation(BlendOperations Operation) = 0;
	virtual BlendOperations GetBlendOperation(void) const = 0;

	virtual void SetSourceBlendFactor(BlendFactors Factor) = 0;
	virtual BlendFactors GetSourceBlendFactor(void) const = 0;

	virtual void SetDestinationBlendFactor(BlendFactors Factor) = 0;
	virtual BlendFactors GetDestinationBlendFactor(void) const = 0;

	virtual void SetAlphaTestFunction(CompareFunctions Function) = 0;
	virtual CompareFunctions GetAlphaTestFunction(void) const = 0;

	virtual void SetAlphaTestReference(uint8 Reference) = 0;
	virtual uint8 GetAlphaTestReference(void) const = 0;

	virtual void SetCullType(CullTypes Mode) = 0;
	virtual CullTypes GetCullType(void) const = 0;

	virtual void SetTextureStage(uint8 Stage, ITexture *Texture) = 0;
	virtual ITexture *GetTextureStage(uint8 Stage = 0) const = 0;

	virtual void SetVertexProgram(IGPUProgram *Program) = 0;
	virtual IGPUProgramUsage *GetVertexProgram(void) = 0;

	virtual void SetFragmentProgram(IGPUProgram *Program) = 0;
	virtual IGPUProgramUsage *GetFragmentProgram(void) = 0;
};

END_NAMESPACE
#endif // IPASS_H

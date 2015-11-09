// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\PassAPI.h>

BEGIN_NAMESPACE

void Pass_SetFillMode(IPass *Pass, IPass::FillMode Mode)
{
	Pass->SetFillMode(Mode);
}


IPass::FillMode Pass_GetFillMode(IPass *Pass)
{
	return Pass->GetFillMode();
}


void Pass_SetZCompareFunction(IPass *Pass, IPass::CompareFunction Function)
{
	Pass->SetZCompareFunction(Function);
}


IPass::CompareFunction Pass_GetZCompareFunction(IPass *Pass)
{
	return Pass->GetZCompareFunction();
}


void Pass_SetZWrite(IPass *Pass, bool Value)
{
	Pass->SetZWrite(Value);
}


bool Pass_GetZWrite(IPass *Pass)
{
	return Pass->GetZWrite();
}


void Pass_SetBlendOperation(IPass *Pass, IPass::BlendOperation Operation)
{
	Pass->SetBlendOperation(Operation);
}


IPass::BlendOperation Pass_GetBlendOperation(IPass *Pass)
{
	return Pass->GetBlendOperation();
}


void Pass_SetSourceBlendFactor(IPass *Pass, IPass::BlendFactor Factor)
{
	Pass->SetSourceBlendFactor(Factor);
}


IPass::BlendFactor Pass_GetSourceBlendFactor(IPass *Pass)
{
	return Pass->GetSourceBlendFactor();
}


void Pass_SetDestinationBlendFactor(IPass *Pass, IPass::BlendFactor Factor)
{
	Pass->SetDestinationBlendFactor(Factor);
}


IPass::BlendFactor Pass_GetDestinationBlendFactor(IPass *Pass)
{
	return Pass->GetDestinationBlendFactor();
}


void Pass_SetAlphaTestFunction(IPass *Pass, IPass::CompareFunction Function)
{
	Pass->SetAlphaTestFunction(Function);
}


IPass::CompareFunction Pass_GetAlphaTestFunction(IPass *Pass)
{
	return Pass->GetAlphaTestFunction();
}


void Pass_SetAlphaTestReference(IPass *Pass, uint8 Reference)
{
	Pass->SetAlphaTestReference(Reference);
}


uint8 Pass_GetAlphaTestReference(IPass *Pass)
{
	return Pass->GetAlphaTestReference();
}


void Pass_SetCullType(IPass *Pass, IPass::CullType Mode)
{
	Pass->SetCullType(Mode);
}


IPass::CullType Pass_GetCullType(IPass *Pass)
{
	return Pass->GetCullType();
}


void Pass_SetTextureStage(IPass *Pass, uint32 Stage, ITexture *Texture)
{
	Pass->SetTextureStage(Stage, Texture);
}


ITexture *Pass_GetTextureStage(IPass *Pass, uint32 Stage)
{
	return Pass->GetTextureStage(Stage);
}


void SetVertexProgram(IPass *Pass, IGPUProgram *Program)
{
	Pass->SetVertexProgram(Program);
}


IGPUProgramUsage *Pass_GetVertexProgram(IPass *Pass)
{
	return Pass->GetVertexProgram();
}


void SetFragmentProgram(IPass *Pass, IGPUProgram *Program)
{
	Pass->SetFragmentProgram(Program);
}


IGPUProgramUsage *Pass_GetFragmentProgram(IPass *Pass)
{
	return Pass->GetFragmentProgram();
}


END_NAMESPACE

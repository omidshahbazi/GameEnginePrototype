// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PASSAPI_H
#define PASSAPI_H
#include <Public\Utilities.h>
#include <Public\IPass.h>

BEGIN_NAMESPACE

API_FUNCTION void Pass_SetFillMode(IPass *Pass, IPass::FillMode Mode);
API_FUNCTION IPass::FillMode Pass_GetFillMode(IPass *Pass);

API_FUNCTION void Pass_SetZCompareFunction(IPass *Pass, IPass::CompareFunction Function);
API_FUNCTION IPass::CompareFunction Pass_GetZCompareFunction(IPass *Pass);

API_FUNCTION void Pass_SetZWrite(IPass *Pass, bool Value);
API_FUNCTION bool Pass_GetZWrite(IPass *Pass);

API_FUNCTION void Pass_SetBlendOperation(IPass *Pass, IPass::BlendOperation Operation);
API_FUNCTION IPass::BlendOperation Pass_GetBlendOperation(IPass *Pass);

API_FUNCTION void Pass_SetSourceBlendFactor(IPass *Pass, IPass::BlendFactor Factor);
API_FUNCTION IPass::BlendFactor Pass_GetSourceBlendFactor(IPass *Pass);

API_FUNCTION void Pass_SetDestinationBlendFactor(IPass *Pass, IPass::BlendFactor Factor);
API_FUNCTION IPass::BlendFactor Pass_GetDestinationBlendFactor(IPass *Pass);

API_FUNCTION void Pass_SetAlphaTestFunction(IPass *Pass, IPass::CompareFunction Function);
API_FUNCTION IPass::CompareFunction Pass_GetAlphaTestFunction(IPass *Pass);

API_FUNCTION void Pass_SetAlphaTestReference(IPass *Pass, uint8 Reference);
API_FUNCTION uint8 Pass_GetAlphaTestReference(IPass *Pass);

API_FUNCTION void Pass_SetCullType(IPass *Pass, IPass::CullType Mode);
API_FUNCTION IPass::CullType Pass_GetCullType(IPass *Pass);

API_FUNCTION void Pass_SetTextureStage(IPass *Pass, uint32 Stage, ITexture *Texture);
API_FUNCTION ITexture *Pass_GetTextureStage(IPass *Pass, uint32 Stage);

API_FUNCTION void Pass_SetVertexProgramSetVertexProgram(IPass *Pass, IGPUProgram *Program);
API_FUNCTION IGPUProgramUsage *Pass_GetVertexProgram(IPass *Pass);

API_FUNCTION void Pass_SetVertexProgramSetFragmentProgram(IPass *Pass, IGPUProgram *Program);
API_FUNCTION IGPUProgramUsage *Pass_GetFragmentProgram(IPass *Pass);

END_NAMESPACE
#endif // PASSAPI_H

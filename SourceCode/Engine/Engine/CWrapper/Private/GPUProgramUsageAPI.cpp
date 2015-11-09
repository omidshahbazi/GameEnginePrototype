// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\GPUProgramUsageAPI.h>

BEGIN_NAMESPACE


void GPUProgramUsage_ClearAutoParams(IGPUProgramUsage *GPUProgramUsage)
{
	GPUProgramUsage->ClearAutoParams();
}


void GPUProgramUsage_SetAutoParam(IGPUProgramUsage *GPUProgramUsage, BSTR Constant, BSTR Param)
{
	GPUProgramUsage->SetAutoParam(TO_String(Constant), TO_String(Param));
}


void GPUProgramUsage_ClearParams(IGPUProgramUsage *GPUProgramUsage)
{
	GPUProgramUsage->ClearParams();
}


void GPUProgramUsage_SetBool(IGPUProgramUsage *GPUProgramUsage, BSTR Name, bool Value)
{
	GPUProgramUsage->SetBool(TO_String(Name), Value);
}


void GPUProgramUsage_SetInteger(IGPUProgramUsage *GPUProgramUsage, BSTR Name, int32 Value)
{
	GPUProgramUsage->SetInteger(TO_String(Name), Value);
}


void GPUProgramUsage_SetFloat(IGPUProgramUsage *GPUProgramUsage, BSTR Name, float32 Value)
{
	GPUProgramUsage->SetFloat(TO_String(Name), Value);
}


void GPUProgramUsage_SetVector2(IGPUProgramUsage *GPUProgramUsage, BSTR Name, const Vector2 &Value)
{
	GPUProgramUsage->SetVector2(TO_String(Name), Value);
}


void GPUProgramUsage_SetVector3(IGPUProgramUsage *GPUProgramUsage, BSTR Name, const Vector3 &Value)
{
	GPUProgramUsage->SetVector3(TO_String(Name), Value);
}


void GPUProgramUsage_SetMatrix(IGPUProgramUsage *GPUProgramUsage, BSTR Name, const Matrix4 &Value)
{
	GPUProgramUsage->SetMatrix(TO_String(Name), Value);
}


IGPUProgram *GPUProgramUsage_GetProgram(IGPUProgramUsage *GPUProgramUsage)
{
	return GPUProgramUsage->GetProgram();
}


END_NAMESPACE

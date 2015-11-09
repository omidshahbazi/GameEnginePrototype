// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GPUPROGRAMUSAGEAPI_H
#define GPUPROGRAMUSAGEAPI_H
#include <Public\Utilities.h>
#include <Public\IGPUProgramUsage.h>
#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\Matrix4.h>

BEGIN_NAMESPACE

API_FUNCTION void GPUProgramUsage_ClearAutoParams(IGPUProgramUsage *GPUProgramUsage);
API_FUNCTION void GPUProgramUsage_SetAutoParam(IGPUProgramUsage *GPUProgramUsage, BSTR Constant, BSTR Param);

API_FUNCTION void GPUProgramUsage_ClearParams(IGPUProgramUsage *GPUProgramUsage);
API_FUNCTION void GPUProgramUsage_SetBool(IGPUProgramUsage *GPUProgramUsage, BSTR Name, bool Value);
API_FUNCTION void GPUProgramUsage_SetInteger(IGPUProgramUsage *GPUProgramUsage, BSTR Name, int32 Value);
API_FUNCTION void GPUProgramUsage_SetFloat(IGPUProgramUsage *GPUProgramUsage, BSTR Name, float32 Value);
API_FUNCTION void GPUProgramUsage_SetVector2(IGPUProgramUsage *GPUProgramUsage, BSTR Name, const Vector2 &Value);
API_FUNCTION void GPUProgramUsage_SetVector3(IGPUProgramUsage *GPUProgramUsage, BSTR Name, const Vector3 &Value);
API_FUNCTION void GPUProgramUsage_SetMatrix(IGPUProgramUsage *GPUProgramUsage, BSTR Name, const Matrix4 &Value);

API_FUNCTION IGPUProgram *GPUProgramUsage_GetProgram(IGPUProgramUsage *GPUProgramUsage);

END_NAMESPACE
#endif // GPUPROGRAMUSAGEAPI_H

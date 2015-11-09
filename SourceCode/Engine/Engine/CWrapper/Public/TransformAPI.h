// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TRANSFORMAPI_H
#define TRANSFORMAPI_H
#include <Public\Utilities.h>
#include <Public\ITransform.h>
#include <Public\Vector3.h>


BEGIN_NAMESPACE

API_FUNCTION ITransform *Transform_GetParent(ITransform *Transform);
API_FUNCTION void Transform_SetParent(ITransform *Transform, ITransform *Parent);

API_FUNCTION Vector3 Transform_GetLocalPosition(ITransform *Transform);
API_FUNCTION void Transform_SetLocalPosition(ITransform *Transform, Vector3 Value);

API_FUNCTION Vector3 Transform_GetLocalRotation(ITransform *Transform);
API_FUNCTION void Transform_SetLocalRotation(ITransform *Transform, Vector3 Value);

API_FUNCTION Vector3 Transform_GetLocalScale(ITransform *Transform);
API_FUNCTION void Transform_SetLocalScale(ITransform *Transform, Vector3 Value);

API_FUNCTION Vector3 Transform_GetPosition(ITransform *Transform);
API_FUNCTION void Transform_SetPosition(ITransform *Transform, Vector3 Value);

API_FUNCTION Vector3 Transform_GetRotation(ITransform *Transform);
API_FUNCTION void Transform_SetRotation(ITransform *Transform, Vector3 Value);

API_FUNCTION Vector3 Transform_GetScale(ITransform *Transform);
API_FUNCTION void Transform_SetScale(ITransform *Transform, Vector3 Value);

API_FUNCTION void Transform_Translate(ITransform *Transform, Vector3 Value);

API_FUNCTION void Transform_Rotate(ITransform *Transform, Vector3 Value);

API_FUNCTION void Transform_Scale(ITransform *Transform, Vector3 Value);

END_NAMESPACE
#endif // TRANSFORMAPI_H

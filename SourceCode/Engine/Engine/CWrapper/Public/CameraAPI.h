// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CAMERAAPI_H
#define CAMERAAPI_H
#include <Public\Utilities.h>
#include <Public\ICamera.h>
#include <Public\Matrix4.h>

BEGIN_NAMESPACE

API_FUNCTION ICamera::ProjectionType Camera_GetProjectionType(ICamera *Camera);
API_FUNCTION void Camera_SetProjectionType(ICamera *Camera, ICamera::ProjectionType Value);

API_FUNCTION float32 Camera_GetFieldOfView(ICamera *Camera);
API_FUNCTION void Camera_SetFieldOfView(ICamera *Camera, float32 Value);

API_FUNCTION Vector2 Camera_GetTargetSize(ICamera *Camera);
API_FUNCTION float32 Camera_GetAspectRatio(ICamera *Camera);

API_FUNCTION float32 Camera_GetNearClipDistance(ICamera *Camera);
API_FUNCTION void Camera_SetNearClipDistance(ICamera *Camera, float32 Value);

API_FUNCTION float32 Camera_GetFarClipDistance(ICamera *Camera);
API_FUNCTION void Camera_SetFarClipDistance(ICamera *Camera, float32 Value);

API_FUNCTION Colour Camera_GetClearColour(ICamera *Camera);
API_FUNCTION void Camera_SetClearColour(ICamera *Camera, Colour Value);

API_FUNCTION const Matrix4 *Camera_GetViewMatrix(ICamera *Camera);
API_FUNCTION const Matrix4 *Camera_GetProjectionMatrix(ICamera *Camera);
API_FUNCTION const Matrix4 *Camera_GetViewProjectionMatrix(ICamera *Camera);

API_FUNCTION void Camera_AddComposite(ICamera *Camera, IComposite *Composite, int8 Index);
API_FUNCTION void Camera_RemoveComposite(ICamera *Camera, IComposite *Composite);
API_FUNCTION void Camera_RemoveCompositeAt(ICamera *Camera, uint8 Index);
API_FUNCTION IComposite *Camera_GetComposite(ICamera *Camera, uint8 Index);
API_FUNCTION uint8 Camera_GetCompositesCount(ICamera *Camera);

END_NAMESPACE
#endif // CAMERAAPI_H

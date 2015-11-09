// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\CameraAPI.h>

BEGIN_NAMESPACE


ICamera::ProjectionType Camera_GetProjectionType(ICamera *Camera)
{
	return Camera->GetProjectionType();
}
void Camera_SetProjectionType(ICamera *Camera, ICamera::ProjectionType Value)
{
	Camera->SetProjectionType(Value);
}

float32 Camera_GetFieldOfView(ICamera *Camera)
{
	return Camera->GetFieldOfView();
}
void Camera_SetFieldOfView(ICamera *Camera, float32 Value)
{
	Camera->SetFieldOfView(Value);
}

Vector2 Camera_GetTargetSize(ICamera *Camera)
{
	return Camera->GetTargetSize();
}
float32 Camera_GetAspectRatio(ICamera *Camera)
{
	return Camera->GetAspectRatio();
}

float32 Camera_GetNearClipDistance(ICamera *Camera)
{
	return Camera->GetNearClipDistance();
}
void Camera_SetNearClipDistance(ICamera *Camera, float32 Value)
{
	Camera->SetNearClipDistance(Value);
}

float32 Camera_GetFarClipDistance(ICamera *Camera)
{
	return Camera->GetFarClipDistance();
}
void Camera_SetFarClipDistance(ICamera *Camera, float32 Value)
{
	Camera->SetFarClipDistance(Value);
}

Colour Camera_GetClearColour(ICamera *Camera)
{
	return Camera->GetClearColour();
}
void Camera_SetClearColour(ICamera *Camera, Colour Value)
{
	Camera->SetClearColour(Value);
}

const Matrix4 *Camera_GetViewMatrix(ICamera *Camera)
{
	return &Camera->GetViewMatrix();
}
const Matrix4 *Camera_GetProjectionMatrix(ICamera *Camera)
{
	return &Camera->GetProjectionMatrix();
}
const Matrix4 *Camera_GetViewProjectionMatrix(ICamera *Camera)
{
	return &Camera->GetViewProjectionMatrix();
}

void Camera_AddComposite(ICamera *Camera, IComposite *Composite, int8 Index)
{
	Camera->AddComposite(Composite, Index);
}
void Camera_RemoveComposite(ICamera *Camera, IComposite *Composite)
{
	Camera->RemoveComposite(Composite);
}
void Camera_RemoveCompositeAt(ICamera *Camera, uint8 Index)
{
	Camera->RemoveCompositeAt(Index);
}
IComposite *Camera_GetComposite(ICamera *Camera, uint8 Index)
{
	return Camera->GetComposite(Index);
}
uint8 Camera_GetCompositesCount(ICamera *Camera)
{
	return (uint8)Camera->GetComposites().GetSize();
}

END_NAMESPACE

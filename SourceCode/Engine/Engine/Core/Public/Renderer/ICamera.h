// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ICAMERA_H
#define ICAMERA_H

#include <Public\Component.h>
#include <Public\Renderer\IPass.h>

BEGIN_NAMESPACE

struct Vector2;
struct Vector3;
struct Matrix4;
struct Colour;
struct BoundingBox;
class IComposite;
	
class ICamera : public Component
{
public:
	typedef Vector<IComposite*> CompositesList;

public:
	enum class ProjectionTypes
	{
		Perspective = 0,
		Orthographic
	};

public:
	virtual ~ICamera(void) {}

	virtual ProjectionTypes GetProjectionType(void) = 0;
	virtual void SetProjectionType(ProjectionTypes Value) = 0;

	virtual float32 GetFieldOfView(void) = 0;
	virtual void SetFieldOfView(float32 Value) = 0;

	virtual const Vector2 &GetTargetSize(void) = 0;
	virtual float32 GetAspectRatio(void) = 0;

	virtual float32 GetNearClipDistance(void) = 0;
	virtual void SetNearClipDistance(float32 Value) = 0;

	virtual float32 GetFarClipDistance(void) = 0;
	virtual void SetFarClipDistance(float32 Value) = 0;

	virtual const Colour &GetClearColour(void) = 0;
	virtual void SetClearColour(const Colour &Value) = 0;

	virtual FillModes GetFillMode(void) = 0;
	virtual void SetFillMode(FillModes Value) = 0;

	virtual bool IsInFrustum(const Vector3 &Position, float Radius) = 0;

	virtual const Matrix4 &GetViewMatrix(void) const = 0;
	virtual const Matrix4 &GetProjectionMatrix(void) const = 0;
	virtual const Matrix4 &GetViewProjectionMatrix(void) const = 0;

	virtual void AddComposite(IComposite *Composite, int8 Index = -1) = 0;
	virtual void RemoveComposite(IComposite *Composite) = 0;
	virtual void RemoveCompositeAt(uint8 Index) = 0;
	virtual IComposite *GetComposite(uint8 Index) = 0;
	virtual const CompositesList &GetComposites(void) const = 0;
};

END_NAMESPACE
#endif // ICAMERA_H

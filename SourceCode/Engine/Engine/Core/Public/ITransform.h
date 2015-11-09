// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ITRANSFORM_H
#define ITRANSFORM_H

#include <Public\Component.h>

BEGIN_NAMESPACE

class IGameObject;
struct Vector3;
struct Matrix4;

REFLECTION_ENUM()
enum class TransformationSpaces
{
	Local = 0,
	World
};

class ITransform : public Component
{
public:
	virtual void SetParent(ITransform *Parent) = 0;
	virtual ITransform *GetParent(void) const = 0;
	
	virtual void SetLocalPosition(float32 X, float32 Y, float32 Z) = 0;
	virtual void SetLocalPosition(const Vector3 &Position) = 0;
	virtual const Vector3 &GetLocalPosition(void) const = 0;
	virtual void SetLocalRotation(float32 X, float32 Y, float32 Z) = 0;
	virtual void SetLocalRotation(const Vector3 &Value) = 0;
	virtual const Vector3 &GetLocalRotation(void) const = 0;
	virtual void SetLocalScale(float32 X, float32 Y, float32 Z) = 0;
	virtual void SetLocalScale(const Vector3 &Scale) = 0;
	virtual const Vector3 &GetLocalScale(void) const = 0;

	virtual void SetPosition(float32 X, float32 Y, float32 Z) = 0;
	virtual void SetPosition(const Vector3 &Position) = 0;
	virtual const Vector3 &GetPosition(void) const = 0;
	virtual void SetRotation(float32 X, float32 Y, float32 Z) = 0;
	virtual void SetRotation(const Vector3 &Value) = 0;
	virtual const Vector3 &GetRotation(void) const = 0;
	virtual void SetScale(float32 X, float32 Y, float32 Z) = 0;
	virtual void SetScale(const Vector3 &Scale) = 0;
	virtual const Vector3 &GetScale(void) const = 0;

	virtual void Translate(float32 X, float32 Y, float32 Z, const TransformationSpaces &Space = TransformationSpaces::World) = 0;
	virtual void Translate(const Vector3 &Value, const TransformationSpaces &Space = TransformationSpaces::World) = 0;
	virtual void Rotate(float32 X, float32 Y, float32 Z, const TransformationSpaces &Space = TransformationSpaces::World) = 0;
	virtual void Rotate(const Vector3 &Value, const TransformationSpaces &Space = TransformationSpaces::World) = 0;
	virtual void Scale(float32 X, float32 Y, float32 Z, const TransformationSpaces &Space = TransformationSpaces::World) = 0;
	virtual void Scale(const Vector3 &Value, const TransformationSpaces &Space = TransformationSpaces::World) = 0;

	virtual Vector3 GetRight(void) const = 0;
	virtual Vector3 GetUp(void) const = 0;
	virtual Vector3 GetForward(void) const = 0;

	virtual const Matrix4 &GetLocalMatrix(void) = 0;
	virtual const Matrix4 &GetWorldMatrix(void) = 0;
};

END_NAMESPACE

#endif // ITRANSFORM_H
// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IFIXTURE_H
#define IFIXTURE_H

#include <Public\ISerializable.h>
#include <Public\IBaseObject.h>

BEGIN_NAMESPACE

class IPhysicsScene;
class IBody;
class IShape;

struct Vector2;

class IFixture : public ISerializable
{
public:
	virtual ~IFixture(void) {}

	virtual IBody *GetBody(void) const = 0;

	virtual void SetName(const String &Name) = 0;
	virtual const String &GetName(void) const = 0;

	virtual void SetDensity(float32 Value) = 0;
	virtual float32 GetDensity(void) const = 0;

	virtual void SetFriction(float32 Value) = 0;
	virtual float32 GetFriction(void) const = 0;

	virtual void SetRestitution(float32 Value) = 0;
	virtual float32 GetRestitution(void) const = 0;

	virtual void SetSensor(const bool Flag) = 0;
	virtual bool IsSensor(void) const = 0;

	virtual void SetCollisionCategoryBits(uint16 Value) = 0;
	virtual const uint16 GetCollisionCategoryBits(void) const = 0;

	virtual void SetCollisionMaskBits(uint16 Value) = 0;
	virtual const uint16 GetCollisionMaskBits(void) const = 0;

	virtual void SetCollisionGroupIndex(uint16 Value) = 0;
	virtual const int16 &GetCollisionGroupIndex(void) const = 0;

	virtual void Prepare(IShape *Shape) = 0;
	virtual void Prepare(float32 radius, const Vector2 &Center) = 0;
	virtual void Prepare(float32 hx, float32 hy, const Vector2 &Center = Vector2()) = 0;
	virtual void Prepare(const List<Vector2> &Vertices) = 0;
	virtual void Prepare(const Vector2 &Vertex1, const Vector2 &Vertex2) = 0;

	virtual IShape *GetShape(void) const = 0;
};

END_NAMESPACE
#endif // IFIXTURE_H

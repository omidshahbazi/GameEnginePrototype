// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FIXTURE_H
#define FIXTURE_H

#include <Public\Physics\IFixture.h>
#include "Box2D/Box2D.h"

BEGIN_NAMESPACE

class Fixture : public IFixture
{
public:
	Fixture(b2Body *Body, const String &Name);

	virtual ~Fixture(void);

	bool Serialize(IAttributes *Attributes);
	bool Deserialize(IAttributes *Attributes);

	IBody *GetBody(void) const;

	void SetName(const String &Name);
	const String &GetName(void) const
	{
		return m_Name;
	}

	void SetDensity(float32 Value);
	float32 GetDensity(void) const
	{
		return m_Density;
	}

	void SetFriction(float32 Value);
	float32 GetFriction(void) const
	{
		return m_Friction;
	}

	void SetRestitution(float32 Value);
	float32 GetRestitution(void) const
	{
		return m_Restitution;
	}

	void SetSensor(const bool Flag);
	bool IsSensor(void) const
	{
		return m_IsSensor;
	}
	void SetCollisionCategoryBits(uint16 Value);
	const unsigned short GetCollisionCategoryBits(void) const
	{
		return m_Fixture->GetFilterData().categoryBits;
	}

	void SetCollisionMaskBits(uint16 Value);
	const unsigned short GetCollisionMaskBits(void) const
	{
		return m_Fixture->GetFilterData().maskBits;
	}

	void SetCollisionGroupIndex(uint16 Value);
	const short &GetCollisionGroupIndex(void) const
	{
		return m_GroupID;
	}

	void Prepare(IShape *Shape);
	void Prepare(float32 radius, const Vector2 &Center);
	void Prepare(float32 hx, float32 hy, const Vector2 &Center = Vector2());
	void Prepare(const List<Vector2> &Vertices);
	void Prepare(const Vector2 &Vertex1, const Vector2 &Vertex2);

	IShape *GetShape(void) const
	{
		return m_Shape;
	}

	void SetBox2DFixture(b2Fixture *Fixture)
	{
		m_Fixture = Fixture;
	}

	b2Fixture *GetBox2DFixture(void) const
	{
		return m_Fixture;
	}

private:
	b2Fixture *CreateFixture(const b2Shape *Shape);
	void DestroyFixture(void);

private:
	b2Body *m_Body;
	b2Fixture *m_Fixture;

	IShape *m_Shape;

	String m_Name;
	float m_Density;
	float m_Friction;
	float m_Restitution;
	bool m_IsSensor;
	short m_GroupID;
};

END_NAMESPACE
#endif // FIXTURE_H

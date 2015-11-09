// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Fixture.h>
#include <Private\PhysicsCommon.h>
#include <Private\CircleShape.h>
#include <Private\BoxShape.h>
#include <Private\PolygonShape.h>
#include <Private\EdgeShape.h>
#include <Public\Physics\IBody.h>
#include <Public\Physics\IPhysicsScene.h>
#include <Public\Physics\IPhysicsEngine.h>
#include <Public\Core.h>
#include <Public\StringConverter.h>


BEGIN_NAMESPACE


Fixture::Fixture(b2Body *Body, const String &Name) :
	m_Body(Body),
	m_Fixture(NULL),
	m_Name(Name),
	m_Density(0.f),
	m_Friction(0.2f),
	m_Restitution(0.f),
	m_IsSensor(false),
	m_GroupID(0),
	m_Shape(NULL)
{
	Prepare(NULL);
}


Fixture::~Fixture(void)
{
#ifndef LAUNCH_MODE
	if (m_Body)
	{
#endif
		m_Body->DestroyFixture(m_Fixture);
		m_Fixture = 0;

		delete m_Shape;
		m_Shape = 0;

#ifndef LAUNCH_MODE
	}
#endif

	LOG_INFO_DEBUG("IFixture [" + m_Name + "] destoryed successfully")
}


bool Fixture::Serialize(IAttributes *Attributes)
{
	Attributes->AddString("Name", m_Name);
	Attributes->AddFloat("Density", m_Fixture->GetDensity());
	Attributes->AddFloat("Friction", m_Fixture->GetFriction());
	Attributes->AddFloat("Restitution", m_Fixture->GetRestitution());
	Attributes->AddBoolean("Sensor", m_Fixture->IsSensor());
	Attributes->AddInteger("CategoryBits", m_Fixture->GetFilterData().categoryBits);
	Attributes->AddInteger("MaskBits", m_Fixture->GetFilterData().maskBits);
	Attributes->AddInteger("GroupIndex", m_Fixture->GetFilterData().groupIndex);
	Attributes->AddInteger("ShapeType", m_Shape->GetType());

	if (m_Shape->GetType() == IShape::ST_CIRCLE)
	{
		Attributes->AddFloat("CircleRadius", static_cast<ICircleShape*>(m_Shape)->GetRadius());
		Attributes->AddVector2("CircleCenter", static_cast<ICircleShape*>(m_Shape)->GetCenter());
	}
	else if (m_Shape->GetType() == IShape::ST_BOX)
	{
		Attributes->AddVector2("BoxSize", static_cast<IBoxShape*>(m_Shape)->GetHalfSize());
		Attributes->AddVector2("BoxCenter", static_cast<IBoxShape*>(m_Shape)->GetCenter());
	}
	else if (m_Shape->GetType() == IShape::ST_POLYGON)
	{
		Attributes->AddInteger("PolygonVertexCount", static_cast<IPolygonShape*>(m_Shape)->GetVertexCount());
		for (unsigned int i = 0; i < static_cast<IPolygonShape*>(m_Shape)->GetVertexCount(); i++)
		{
			Attributes->AddVector2("PolygonVertex" + StringConverter::ToString(i), static_cast<IPolygonShape*>(m_Shape)->GetVertices()[i]);
		}
	}
	else if (m_Shape->GetType() == IShape::ST_EDGE)
	{
		Attributes->AddVector2("EdgeBeginPoint", static_cast<IEdgeShape*>(m_Shape)->GetBeginPoint());
		Attributes->AddVector2("EdgeEndPoint", static_cast<IEdgeShape*>(m_Shape)->GetEndPoint());
	}

	return true;
}


bool Fixture::Deserialize(IAttributes *Attributes)
{
	Vector2 HalfSize;
	IShape::ShapeType type = (IShape::ShapeType)Attributes->GetInteger("ShapeType");

	if (type == IShape::ST_CIRCLE)
	{
		Prepare(Attributes->GetFloat("CircleRadius"), Attributes->GetVector2("CircleCenter"));
	}
	else if (type == IShape::ST_BOX)
	{
		HalfSize = Attributes->GetVector2("BoxSize");
		Prepare(HalfSize.X, HalfSize.Y, Attributes->GetVector2("BoxCenter"));
	}
	else if (type == IShape::ST_POLYGON)
	{
		unsigned int VertexCount = Attributes->GetInteger("PolygonVertexCount");

		List<Vector2> Vertices;
		for (unsigned int i = 0; i < VertexCount; i++)
		{
			Vertices.Add(Attributes->GetVector2("PolygonVertex" + StringConverter::ToString(i)));
		}

		Prepare(Vertices);
	}
	else if (type == IShape::ST_EDGE)
	{
		Prepare(Attributes->GetVector2("EdgeBeginPoint"), Attributes->GetVector2("EdgeEndPoint"));
	}

	SetDensity(Attributes->GetFloat("Density"));
	SetFriction(Attributes->GetFloat("Friction"));
	SetRestitution(Attributes->GetFloat("Restitution"));
	SetSensor(Attributes->GetBoolean("Sensor"));
	SetCollisionCategoryBits(Attributes->GetInteger("CategoryBits"));
	//SetCollisionMaskBits(Attributes->GetFloat("MaskBits"));
	SetCollisionGroupIndex(Attributes->GetInteger("GroupIndex"));

	return true;
}


IBody *Fixture::GetBody(void) const
{
	return ((IBody*)m_Body->GetUserData());
}


void Fixture::SetName(const String &Name)
{
	if (Name == "")
	{
		LOG_ERROR("Fixture name cannot be set to null");
		return;
	}

	if (static_cast<IBody*>(m_Body->GetUserData())->GetFixture(Name))
	{
		LOG_ERROR("Fixture with the name " + Name + " already exists");
		return;
	}

	m_Name = Name;
}


void Fixture::SetDensity(float32 Value)
{
	m_Density = Value;
	m_Fixture->SetDensity(Value);
	m_Body->ResetMassData();
}


void Fixture::SetFriction(float32 Value)
{
	m_Friction = Value;
	m_Fixture->SetFriction(Value);
}


void Fixture::SetRestitution(float32 Value)
{
	m_Restitution = Value;
	m_Fixture->SetRestitution(Value);
}


void Fixture::SetSensor(const bool Flag)
{
	m_IsSensor = Flag;
	m_Fixture->SetSensor(Flag);
}


void Fixture::SetCollisionCategoryBits(uint16 Value)
{
	b2Filter data = m_Fixture->GetFilterData();
	data.categoryBits = Value;
	m_Fixture->SetFilterData(data);
}


void Fixture::SetCollisionMaskBits(uint16 Value)
{
	b2Filter data = m_Fixture->GetFilterData();
	data.maskBits = Value;
	m_Fixture->SetFilterData(data);
}


void Fixture::SetCollisionGroupIndex(uint16 Value)
{
	m_GroupID = Value;
	b2Filter data = m_Fixture->GetFilterData();
	data.groupIndex = Value;
	m_Fixture->SetFilterData(data);
}


void Fixture::Prepare(IShape *Shape)
{
	if (!Shape)
		return;

	const IShape::ShapeType &type = Shape->GetType();

	if (type == IShape::ST_BOX)
	{
		IBoxShape *box = static_cast<IBoxShape*>(Shape);
		const Vector2 &halfSize = box->GetHalfSize();
		Prepare(halfSize.X, halfSize.Y, box->GetCenter());
	}
	else if (type == IShape::ST_CIRCLE)
	{
		ICircleShape *circle = static_cast<ICircleShape*>(Shape);
		Prepare(circle->GetRadius(), circle->GetCenter());
	}
	else if (type == IShape::ST_EDGE)
	{
		IEdgeShape *edge = static_cast<IEdgeShape*>(Shape);
		Prepare(edge->GetBeginPoint(), edge->GetEndPoint());
	}
	else if (type == IShape::ST_POLYGON)
	{
		IPolygonShape *polygon = static_cast<IPolygonShape*>(Shape);
		Prepare(polygon->GetVertices());
	}
}


void Fixture::Prepare(float32 radius, const Vector2 &Position)
{
	DestroyFixture();

	b2CircleShape shape;
	shape.m_radius = radius;
	shape.m_p = Tob2Vec2(Position);
	m_Fixture = CreateFixture(&shape);

	m_Shape = new CircleShape(static_cast<b2CircleShape*>(m_Fixture->GetShape()));
}


void Fixture::Prepare(float32 hx, float32 hy, const Vector2 &Center)
{
	DestroyFixture();

	b2PolygonShape shape;
	shape.SetAsBox(hx, hy);
	shape.m_centroid = Tob2Vec2(Center);
	m_Fixture = CreateFixture(&shape);

	m_Shape = new BoxShape(static_cast<b2PolygonShape*>(m_Fixture->GetShape()), Vector2(hx, hy));
}


void Fixture::Prepare(const List<Vector2> &Vertices)
{
	DestroyFixture();

	b2PolygonShape shape;
	shape.Set(Tob2Vec2(Vertices), Vertices.GetSize());
	m_Fixture = CreateFixture(&shape);

	m_Shape = new PolygonShape(static_cast<b2PolygonShape*>(m_Fixture->GetShape()));
}


void Fixture::Prepare(const Vector2 &Vertex1, const Vector2 &Vertex2)
{
	DestroyFixture();

	b2EdgeShape shape;
	shape.Set(Tob2Vec2(Vertex1), Tob2Vec2(Vertex2));
	m_Fixture = CreateFixture(&shape);

	m_Shape = new EdgeShape(static_cast<b2EdgeShape*>(m_Fixture->GetShape()));
}


b2Fixture *Fixture::CreateFixture(const b2Shape *Shape)
{
	b2FixtureDef *fixtureDef = new b2FixtureDef();
	fixtureDef->shape = Shape;
	if (m_Body->GetType() == b2_dynamicBody)
		fixtureDef->density = 1;

	b2Fixture *Fixture = m_Body->CreateFixture(fixtureDef);

	delete fixtureDef;
	fixtureDef = NULL;

	Fixture->SetUserData(this);
	return Fixture;
}


void Fixture::DestroyFixture(void)
{
	if (m_Fixture)
	{
		m_Body->DestroyFixture(m_Fixture);
		delete m_Shape;
	}
}


END_NAMESPACE

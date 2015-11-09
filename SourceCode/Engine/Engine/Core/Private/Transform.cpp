// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Transform.h>
#include <Private\Scene.h>


BEGIN_NAMESPACE


Transform::Transform(ITransform *Parent) :
m_Parent(NULL),
m_LocalMatrix(true),
m_WorldMatrix(true),
m_LocalScale(Vector3::ONE),
m_LocalRotation(0.0F),
m_WorldScale(Vector3::ONE),
m_WorldRotation(0.0F),
m_IsLocalMatrixDirty(true),
m_IsWorldMatrixDirty(false)
{
	if (Parent)
		SetParent(Parent);
}


Transform::~Transform(void)
{
	FOR_EACH(object, m_Children)
		delete &object;
}


void Transform::Update(void)
{
	if (m_IsLocalMatrixDirty)
		UpdateLocalMatrix();
	else if (m_IsWorldMatrixDirty)
		UpdateWorldMatrix();
}


void Transform::SetParent(ITransform *Parent)
{
	if (m_Parent == Parent || (Parent && Parent->GetParent() == this))
		return;

	UpdateLocalMatrix();

	static Vector3 pos;
	static Vector3 rot;
	static Vector3 scale;

	if (Parent)
	{
		static Matrix4 mat;
		mat = Parent->GetWorldMatrix().GetInverse() * m_WorldMatrix;

		pos = mat.GetPosition();
		rot = mat.GetRotation();
		scale = mat.GetScale();
	}
	else
	{
		pos = m_WorldPosition;
		rot = m_WorldRotation;
		scale = m_WorldScale;
	}

	if (m_Parent)
	{
		TransformsList &children = ((Transform*)m_Parent)->m_Children;
		children.Remove(this);
	}

	m_Parent = (Transform*)Parent;

	if (m_Parent)
		((Transform*)m_Parent)->m_Children.Add(this);

	m_LocalPosition = pos;
	m_LocalRotation = rot;
	m_LocalScale = scale;

	UpdateLocalMatrix();
}


void Transform::UpdateLocalMatrix(void)
{
	m_LocalMatrix.SetRotation(m_LocalRotation);
	m_LocalMatrix.SetPosition(m_LocalPosition);

	if (m_LocalScale != Vector3::ONE)
	{
		static Matrix4 scaleMat(true);
		scaleMat.SetScale(m_LocalScale);
		m_LocalMatrix *= scaleMat;
	}

	UpdateMatrices();

	m_IsLocalMatrixDirty = false;
}


void Transform::UpdateWorldMatrix(void)
{
	m_WorldMatrix.SetRotation(m_WorldRotation);
	m_WorldMatrix.SetPosition(m_WorldPosition);

	if (m_WorldScale != Vector3::ONE)
	{
		static Matrix4 scaleMat(true);
		scaleMat.SetScale(m_WorldScale);
		m_WorldMatrix *= scaleMat;
	}

	if (m_Parent)
		m_LocalMatrix = m_Parent->m_WorldMatrix.GetInverse() * m_WorldMatrix;
	else
		m_LocalMatrix = m_WorldMatrix;

	m_LocalPosition = m_WorldMatrix.GetPosition();
	m_LocalRotation = m_WorldMatrix.GetRotation();
	m_LocalScale = m_WorldMatrix.GetScale();

	NotifyChildrenToUpdateMatrix();

	m_IsWorldMatrixDirty = false;
}

END_NAMESPACE

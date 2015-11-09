// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Public\ITransform.h>
#include <Public\IGameObject.h>
#include <Public\Matrix4.h>
#include <Public\Vector3.h>

BEGIN_NAMESPACE

class Transform : public ITransform
{
private:
	typedef Vector<Transform*> TransformsList;

public:
	Transform(ITransform *Parent = NULL);
	virtual ~Transform(void);

	void Update(void);

	void SetParent(ITransform *Parent);
	ITransform *GetParent(void) const
	{
		return m_Parent;
	}

	void SetLocalPosition(float32 X, float32 Y, float32 Z)
	{
		if (m_LocalPosition.X == X &&
			m_LocalPosition.Y == Y &&
			m_LocalPosition.Z == Z)
			return;

		m_LocalPosition.X = X;
		m_LocalPosition.Y = Y;
		m_LocalPosition.Z = Z;

		m_IsLocalMatrixDirty = true;
		m_IsWorldMatrixDirty = false;
	}

	void SetLocalPosition(const Vector3 &Position)
	{
		if (m_LocalPosition == Position)
			return;

		m_LocalPosition = Position;

		m_IsLocalMatrixDirty = true;
		m_IsWorldMatrixDirty = false;
	}

	const Vector3 &GetLocalPosition(void) const
	{
		return m_LocalPosition;
	}

	void SetLocalRotation(float32 X, float32 Y, float32 Z)
	{
		if (m_LocalRotation.X == X &&
			m_LocalRotation.Y == Y &&
			m_LocalRotation.Z == Z)
			return;

		m_LocalRotation.X = X;
		m_LocalRotation.Y = Y;
		m_LocalRotation.Z = Z;

		m_IsLocalMatrixDirty = true;
		m_IsWorldMatrixDirty = false;
	}

	void SetLocalRotation(const Vector3 &Value)
	{
		if (m_LocalRotation == Value)
			return;

		m_LocalRotation = Value;

		m_IsLocalMatrixDirty = true;
		m_IsWorldMatrixDirty = false;
	}

	const Vector3 &GetLocalRotation(void) const
	{
		return m_LocalRotation;
	}

	void SetLocalScale(float32 X, float32 Y, float32 Z)
	{
		if (m_LocalScale.X == X &&
			m_LocalScale.Y == Y &&
			m_LocalScale.Z == Z)
			return;

		m_LocalScale.X = X;
		m_LocalScale.Y = Y;
		m_LocalScale.Z = Z;

		m_IsLocalMatrixDirty = true;
		m_IsWorldMatrixDirty = false;
	}

	void SetLocalScale(const Vector3 &Scale)
	{
		if (m_LocalScale == Scale)
			return;

		m_LocalScale = Scale;

		m_IsLocalMatrixDirty = true;
		m_IsWorldMatrixDirty = false;
	}

	const Vector3 &GetLocalScale(void) const
	{
		return m_LocalScale;
	}

	void SetPosition(float32 X, float32 Y, float32 Z)
	{
		if (m_WorldPosition.X == X &&
			m_WorldPosition.Y == Y &&
			m_WorldPosition.Z == Z)
			return;

		m_WorldPosition.X = X;
		m_WorldPosition.Y = Y;
		m_WorldPosition.Z = Z;

		m_IsWorldMatrixDirty = true;
		m_IsLocalMatrixDirty = false;
	}

	void SetPosition(const Vector3 &Position)
	{
		if (m_WorldPosition == Position)
			return;

		m_WorldPosition = Position;

		m_IsWorldMatrixDirty = true;
		m_IsLocalMatrixDirty = false;
	}

	const Vector3 &GetPosition(void) const
	{
		return m_WorldPosition;
	}

	void SetRotation(float32 X, float32 Y, float32 Z)
	{
		if (m_LocalRotation.X == X &&
			m_LocalRotation.Y == Y &&
			m_LocalRotation.Z == Z)
			return;

		m_LocalRotation.X = X;
		m_LocalRotation.Y = Y;
		m_LocalRotation.Z = Z;

		m_IsWorldMatrixDirty = true;
		m_IsLocalMatrixDirty = false;
	}

	void SetRotation(const Vector3 &Value)
	{
		if (m_LocalRotation == Value)
			return;

		m_WorldRotation = Value;

		m_IsWorldMatrixDirty = true;
		m_IsLocalMatrixDirty = false;
	}

	const Vector3 &GetRotation(void) const
	{
		return m_WorldRotation;
	}

	void SetScale(float32 X, float32 Y, float32 Z)
	{
		if (m_WorldScale.X == X &&
			m_WorldScale.Y == Y &&
			m_WorldScale.Z == Z)
			return;

		m_WorldScale.X = X;
		m_WorldScale.Y = Y;
		m_WorldScale.Z = Z;

		m_IsWorldMatrixDirty = true;
		m_IsLocalMatrixDirty = false;
	}

	void SetScale(const Vector3 &Scale)
	{
		if (m_WorldScale == Scale)
			return;

		m_WorldScale = Scale;

		m_IsWorldMatrixDirty = true;
		m_IsLocalMatrixDirty = false;
	}

	const Vector3 &GetScale(void) const
	{
		return m_WorldScale;
	}

	void Translate(float32 X, float32 Y, float32 Z, const TransformationSpaces &Space = TransformationSpaces::World)
	{
		if (X == 0.0F &&
			Y == 0.0F  &&
			Z == 0.0F)
			return;

		if (Space == TransformationSpaces::Local)
		{
			m_LocalPosition.X += X;
			m_LocalPosition.Y += Y;
			m_LocalPosition.Z += Z;

			m_IsLocalMatrixDirty = true;
			m_IsWorldMatrixDirty = false;
		}
		else
		{
			m_WorldPosition.X += X;
			m_WorldPosition.Y += Y;
			m_WorldPosition.Z += Z;

			m_IsWorldMatrixDirty = true;
			m_IsLocalMatrixDirty = false;
		}
	}

	void Translate(const Vector3 &Value, const TransformationSpaces &Space = TransformationSpaces::World)
	{
		if (Value == Vector3::ZERO)
			return;

		if (Space == TransformationSpaces::Local)
		{
			m_LocalPosition += Value;

			m_IsLocalMatrixDirty = true;
			m_IsWorldMatrixDirty = false;
		}
		else
		{
			m_WorldPosition += Value;

			m_IsWorldMatrixDirty = true;
			m_IsLocalMatrixDirty = false;
		}
	}

	void Rotate(float32 X, float32 Y, float32 Z, const TransformationSpaces &Space = TransformationSpaces::World)
	{
		if (X == 0.0F &&
			Y == 0.0F  &&
			Z == 0.0F)
			return;

		if (Space == TransformationSpaces::Local)
		{
			m_LocalRotation.X += X;
			m_LocalRotation.Y += Y;
			m_LocalRotation.Z += Z;

			m_IsLocalMatrixDirty = true;
			m_IsWorldMatrixDirty = false;
		}
		else
		{
			m_WorldRotation.X += X;
			m_WorldRotation.Y += Y;
			m_WorldRotation.Z += Z;

			m_IsWorldMatrixDirty = true;
			m_IsLocalMatrixDirty = false;
		}
	}

	void Rotate(const Vector3 &Value, const TransformationSpaces &Space = TransformationSpaces::World)
	{
		if (Value == Vector3::ZERO)
			return;

		if (Space == TransformationSpaces::Local)
		{
			m_LocalRotation += Value;

			m_IsLocalMatrixDirty = true;
			m_IsWorldMatrixDirty = false;
		}
		else
		{
			m_WorldRotation += Value;

			m_IsWorldMatrixDirty = true;
			m_IsLocalMatrixDirty = false;
		}
	}

	void Scale(float32 X, float32 Y, float32 Z, const TransformationSpaces &Space = TransformationSpaces::World)
	{
		if (X == 0.0F &&
			Y == 0.0F &&
			Z == 0.0F)
			return;

		if (Space == TransformationSpaces::Local)
		{
			m_LocalScale.X += X;
			m_LocalScale.Y += Y;
			m_LocalScale.Z += Z;

			m_IsLocalMatrixDirty = true;
			m_IsWorldMatrixDirty = false;
		}
		else
		{
			m_WorldScale.X += X;
			m_WorldScale.Y += Y;
			m_WorldScale.Z += Z;

			m_IsWorldMatrixDirty = true;
			m_IsLocalMatrixDirty = false;
		}
	}

	void Scale(const Vector3 &Value, const TransformationSpaces &Space = TransformationSpaces::World)
	{
		if (Value == Vector3::ZERO)
			return;

		if (Space == TransformationSpaces::Local)
		{
			m_LocalScale += Value;

			m_IsLocalMatrixDirty = true;
			m_IsWorldMatrixDirty = false;
		}
		else
		{
			m_WorldScale += Value;

			m_IsWorldMatrixDirty = true;
			m_IsLocalMatrixDirty = false;
		}
	}

	Vector3 GetRight(void) const
	{
		return m_WorldMatrix.GetRight();
	}

	Vector3 GetUp(void) const
	{
		return m_WorldMatrix.GetUp();
	}

	Vector3 GetForward(void) const
	{
		return m_WorldMatrix.GetForward();
	}

	const Matrix4 &GetLocalMatrix(void)
	{
		if (m_IsLocalMatrixDirty)
			UpdateLocalMatrix();
		else if (m_IsWorldMatrixDirty)
			UpdateWorldMatrix();

		return m_LocalMatrix;
	}

	const Matrix4 &GetWorldMatrix(void)
	{
		if (m_IsWorldMatrixDirty)
			UpdateWorldMatrix(); 
		else if (m_IsLocalMatrixDirty)
			UpdateLocalMatrix();

		return m_WorldMatrix;
	}

	INLINE const TransformsList &GetChildren(void) const
	{
		return m_Children;
	}

private:
	void UpdateLocalMatrix(void);
	void UpdateWorldMatrix(void);

	INLINE void UpdateMatrices(void)
	{
		if (m_Parent)
			m_WorldMatrix = m_Parent->m_WorldMatrix * m_LocalMatrix;
		else
			m_WorldMatrix = m_LocalMatrix;

		m_WorldPosition = m_WorldMatrix.GetPosition();
		m_WorldRotation = m_WorldMatrix.GetRotation();
		m_WorldScale = m_WorldMatrix.GetScale();

		NotifyChildrenToUpdateMatrix();
	}

	INLINE void NotifyChildrenToUpdateMatrix(void)
	{
		FOR_EACH(object, m_Children)
			object->m_IsLocalMatrixDirty = true;
	}

private:
	Transform *m_Parent;

	Matrix4 m_LocalMatrix;
	Matrix4 m_WorldMatrix;

	Vector3 m_LocalPosition;
	Vector3 m_LocalRotation;
	Vector3 m_LocalScale;

	Vector3 m_WorldPosition;
	Vector3 m_WorldRotation;
	Vector3 m_WorldScale;

	bool m_IsLocalMatrixDirty;
	bool m_IsWorldMatrixDirty;

	TransformsList m_Children;
};

END_NAMESPACE
#endif // TRANSFORM_H

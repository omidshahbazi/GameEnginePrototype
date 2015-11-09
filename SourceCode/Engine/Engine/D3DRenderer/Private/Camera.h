// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CAMERA_H
#define CAMERA_H
#include <Public\Renderer\ICamera.h>
#include <Public\ITransform.h>
#include <Public\Vector2.h>
#include <Public\Matrix4.h>
#include <Public\Colour.h>
#include <Private\DirectXInclude.h>
#include <Camera.Reflection.h>

BEGIN_NAMESPACE

REFLECTION_OBJECT()
class Camera : public ICamera
{
	CAMERA_OBJECT()

public:
	Camera(void);
	//Camera(ICamera *PTR);

	void Awake(void);
	void PreUpdate(void);

	ProjectionTypes GetProjectionType(void)
	{
		return m_ProjectionType;
	}
	void SetProjectionType(ProjectionTypes Value)
	{
		if (m_ProjectionType == Value)
			return;

		m_ProjectionType = Value;

		m_IsDirty = true;
	}

	float32 GetFieldOfView(void)
	{
		return m_FieldOfView;
	}
	void SetFieldOfView(float32 Value)
	{
		if (m_FieldOfView == Value)
			return;

		m_FieldOfView = Value;

		m_IsDirty = true;
	}

	const Vector2 &GetTargetSize(void)
	{
		return m_TargetSize;
	}
	float32 GetAspectRatio(void)
	{
		return m_AspectRatio;
	}

	float32 GetNearClipDistance(void)
	{
		return m_NearClipDistance;
	}
	void SetNearClipDistance(float32 Value)
	{
		if (m_NearClipDistance == Value)
			return;

		m_NearClipDistance = Value;

		m_IsDirty = true;
	}

	float32 GetFarClipDistance(void)
	{
		return m_FarClipDistance;
	}
	void SetFarClipDistance(float32 Value)
	{
		if (m_FarClipDistance == Value)
			return;

		m_FarClipDistance = Value;

		m_IsDirty = true;
	}

	const Colour &GetClearColour(void)
	{
		return m_ClearColour;
	}
	void SetClearColour(const Colour &Value)
	{
		m_ClearColour = Value;
	}

	FillModes GetFillMode(void)
	{
		return m_FillMode;
	}
	void SetFillMode(FillModes Value)
	{
		m_FillMode = Value;
	}

	bool IsInFrustum(const Vector3 &Position, float Radius);

	const Matrix4 &GetViewMatrix(void) const
	{
		return m_View;
	}
	const Matrix4 &GetProjectionMatrix(void) const
	{
		return m_Projection;
	}
	const Matrix4 &GetViewProjectionMatrix(void) const
	{
		return m_ViewProjection;
	}

	void AddComposite(IComposite *Composite, int8 Index = -1)
	{
		if (Index < 0)
			m_Composites.Add(Composite);
		else
			m_Composites.Insert(Index, Composite);
	}
	void RemoveComposite(IComposite *Composite)
	{
		m_Composites.Remove(Composite);
	}
	void RemoveCompositeAt(uint8 Index)
	{
		m_Composites.RemoveAt(Index);
	}
	IComposite *GetComposite(uint8 Index)
	{
		return m_Composites[Index];
	}
	const CompositesList &GetComposites(void) const
	{
		return m_Composites;
	}

	void SetTargetSize(const Vector2 &Size);

private:
	void UpdateMatrices(void);

private:
	ITransform *m_Transform;
	Matrix4 m_View;
	Matrix4 m_Projection;
	Matrix4 m_ViewProjection;

	ProjectionTypes m_ProjectionType;
	bool m_IsDirty;
	REFLECTION_PROPERTY()
	float32 m_FieldOfView;
	Vector2 m_TargetSize;
	float32 m_AspectRatio;
	float32 m_NearClipDistance;
	float32 m_FarClipDistance;
	Colour m_ClearColour;
	FillModes m_FillMode;

	D3DXPLANE m_Frustum[6];

	CompositesList m_Composites;
};

END_NAMESPACE
#endif // CAMERA_H

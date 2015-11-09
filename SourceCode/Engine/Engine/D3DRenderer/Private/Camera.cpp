// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Camera.h>
#include <Public\Core.h>
#include <Public\IGameObject.h>
#include <Public\Renderer\IRenderEngine.h>
#include <Public\CMath.h>

#include <Private\Renderer.h>

BEGIN_NAMESPACE


Camera::Camera(void) :
m_View(false),
m_Projection(false),
m_ViewProjection(false),
m_ProjectionType(ProjectionTypes::Perspective),
m_IsDirty(true),
m_FieldOfView(60.0F),
m_NearClipDistance(0.01F),
m_FarClipDistance(100.0F),
m_ClearColour(Colour::BLACK)
{
}


void Camera::Awake(void)
{
	m_Transform = GetHolder()->GetTransform();
}


void Camera::PreUpdate(void)
{
	m_View = m_Transform->GetWorldMatrix().GetInverse();

	UpdateMatrices();
}


bool Camera::IsInFrustum(const Vector3 &Position, float Radius)
{
	for (uint8 i = 0; i < 6; i++)
		if (D3DXPlaneDotCoord(&m_Frustum[i], (D3DXVECTOR3*)(void*)&Position) + Radius < 0)
		{
			// Outside the frustum, reject it!
			return false;
		}

	return true;
}


void Camera::SetTargetSize(const Vector2 &Size)
{
	if (m_TargetSize == Size)
		return;

	m_TargetSize = Size;
	m_AspectRatio = m_TargetSize.X / m_TargetSize.Y;

	m_IsDirty = true;
	UpdateMatrices();
}


void Camera::UpdateMatrices(void)
{
	//static IRenderEngine *renderer = Core::GetReference().GetRenderer();

	if (m_IsDirty)
	{
		if (m_AspectRatio)
		if (m_ProjectionType == ProjectionTypes::Perspective)
			m_Projection.MakePerspectiveProjectionMatrix(m_FieldOfView, m_AspectRatio, m_NearClipDistance, m_FarClipDistance);
		else
			m_Projection.MakeOrthographicProjectionMatrix(m_TargetSize.X, m_TargetSize.Y, m_NearClipDistance, m_FarClipDistance);
		else
			m_Projection.MakeIdentity();

		m_IsDirty = false;
	}

	m_ViewProjection = m_Projection * m_View;

	//renderer->SetViewMatrix(m_View);
	//renderer->SetProjectionMatrix(m_Projection);

	D3DXVECTOR4 col0(m_ViewProjection(0, 0), m_ViewProjection(1, 0), m_ViewProjection(2, 0), m_ViewProjection(3, 0));
	D3DXVECTOR4 col1(m_ViewProjection(0, 1), m_ViewProjection(1, 1), m_ViewProjection(2, 1), m_ViewProjection(3, 1));
	D3DXVECTOR4 col2(m_ViewProjection(0, 2), m_ViewProjection(1, 2), m_ViewProjection(2, 2), m_ViewProjection(3, 2));
	D3DXVECTOR4 col3(m_ViewProjection(0, 3), m_ViewProjection(1, 3), m_ViewProjection(2, 3), m_ViewProjection(3, 3));

	m_Frustum[0] = (D3DXPLANE)col2; // Near
	m_Frustum[1] = (D3DXPLANE)(col3 - col2); // Far
	m_Frustum[2] = (D3DXPLANE)(col3 + col0); // Left
	m_Frustum[3] = (D3DXPLANE)(col3 - col0); // Right
	m_Frustum[4] = (D3DXPLANE)(col3 - col1); // Top
	m_Frustum[5] = (D3DXPLANE)(col3 + col1); // Bottom

	// Normalize planes
	for (uint8 i = 0; i < 6; i++)
		D3DXPlaneNormalize(&m_Frustum[i], &m_Frustum[i]);
}


END_NAMESPACE

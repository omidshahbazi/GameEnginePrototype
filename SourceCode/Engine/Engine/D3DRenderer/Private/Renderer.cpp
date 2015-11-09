// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Renderer.h>
#include <Public\Core.h>
#include <Public\IScene.h>
#include <Public\IGameObject.h>
#include <Public\ITransform.h>
#include <Public\Matrix4.h>
#include <Public\Renderer\GPUParamDefinition.h>
#include <Public\Renderer\ICamera.h>
#include <Private\RendererCommon.h>

BEGIN_NAMESPACE


const float32 HALF_UNIT = 0.5F;

Renderer::Renderer(void) :
m_Material(NULL),
m_Mesh(NULL)
{
}

//Renderer::~Renderer(void)
//{
//}


void Renderer::Awake(void)
{
	m_Transform = GetHolder()->GetTransform();
}


//void Renderer::Update(void)
//{
//	m_OrientedBoundinBox.Reset();
//
//	if (!m_Mesh)
//		return;
//
//	m_OrientedBoundinBox = ;
//
//	Vector3 lower = m_OrientedBoundinBox.GetLowerCorner(),
//		upper = m_OrientedBoundinBox.GetUpperCorner();
//	const Matrix4 &worldMatrix = m_Transform->GetWorldMatrix();
//	//worldMatrix.TransformVector(lower);
//	//worldMatrix.TransformVector(upper);
//	worldMatrix.TranslateVector(lower);
//	worldMatrix.TranslateVector(upper);
//	m_OrientedBoundinBox.SetLowerCorner(lower);
//	m_OrientedBoundinBox.SetUpperCorner(upper);
//}


void Renderer::Render(void)
{
	if (!m_Mesh)
		return;

	static RenderEngine *engine = (RenderEngine*)Core::GetReference().GetRenderer();

	engine->DrawRenderer(this);
}


END_NAMESPACE

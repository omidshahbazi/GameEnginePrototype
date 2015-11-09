// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERER_H
#define RENDERER_H

#include <Public\Renderer\IRenderer.h>
#include <Public\IScene.h>
#include <Public\IGameObject.h>
#include <Private\RenderEngine.h>
#include <Private\Material.h>
#include <Public\BoundingBox.h>
#include <Renderer.Reflection.h>

BEGIN_NAMESPACE

REFLECTION_OBJECT()
class Renderer : public IRenderer
{
	RENDERER_OBJECT()

public:
	Renderer(void);
	//virtual ~Renderer(void);

	void Awake(void);
	//void Update(void);
	void Render(void);

	void SetMaterial(IMaterial *Material)
	{
		m_Material = Material;
	}
	IMaterial *GetMaterial(void)
	{
		return m_Material;
	}
	IMaterial *GetMaterial(void) const
	{
		return m_Material;
	}

	void SetMesh(IMesh *Mesh)
	{
		m_Mesh = Mesh;
	}

	IMesh *GetMesh(void)
	{
		return m_Mesh;
	}

	const BoundingBox &GetOrientedBoundinBox(void) const
	{
		return m_OrientedBoundinBox;
	}

public:
	IMaterial *m_Material;
	IMesh *m_Mesh;
	BoundingBox m_OrientedBoundinBox;

	ITransform *m_Transform;
};

END_NAMESPACE
#endif // RENDERER_H

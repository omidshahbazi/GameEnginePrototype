// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\RendererAPI.h>

BEGIN_NAMESPACE


void Renderer_SetMaterial(IRenderer *Renderer, IMaterial *Material)
{
	Renderer->SetMaterial(Material);
}
IMaterial *Renderer_GetMaterial(IRenderer *Renderer)
{
	return Renderer->GetMaterial();
}

void Renderer_SetMesh(IRenderer *Renderer, IMesh *Mesh)
{
	Renderer->SetMesh(Mesh);
}
IMesh *Renderer_GetMesh(IRenderer *Renderer)
{
	return Renderer->GetMesh();
}

BoundingBox Renderer_GetOrientedBoundinBox(IRenderer *Renderer)
{
	return Renderer->GetOrientedBoundinBox();
}


END_NAMESPACE

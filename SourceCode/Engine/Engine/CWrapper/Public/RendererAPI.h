// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERERAPI_H
#define RENDERERAPI_H
#include <Public\Utilities.h>
#include <Public\IRenderer.h>
#include <Public\BoundingBox.h>

BEGIN_NAMESPACE

API_FUNCTION void Renderer_SetMaterial(IRenderer *Renderer, IMaterial *Material);
API_FUNCTION IMaterial *Renderer_GetMaterial(IRenderer *Renderer);

API_FUNCTION void Renderer_SetMesh(IRenderer *Renderer, IMesh *Mesh);
API_FUNCTION IMesh *Renderer_GetMesh(IRenderer *Renderer);

API_FUNCTION BoundingBox Renderer_GetOrientedBoundinBox(IRenderer *Renderer);

END_NAMESPACE
#endif // RENDERERAPI_H

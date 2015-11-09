// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IRENDERER_H
#define IRENDERER_H

#include <Public\ISerializable.h>
#include <Public\Component.h>

BEGIN_NAMESPACE

class IMaterial;
class IMesh;
struct BoundingBox;

class IRenderer : public Component, public ISerializable
{
public:
	virtual ~IRenderer(void) {}

	virtual void SetMaterial(IMaterial *Material) = 0;
	virtual IMaterial *GetMaterial(void) = 0;
	virtual IMaterial *GetMaterial(void) const = 0;

	virtual void SetMesh(IMesh *Mesh) = 0;
	virtual IMesh *GetMesh(void) = 0;

	virtual const BoundingBox &GetOrientedBoundinBox(void) const = 0;
};

END_NAMESPACE
#endif // IRENDERER_H

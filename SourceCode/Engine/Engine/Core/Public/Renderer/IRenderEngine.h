// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IRENDERENGINE_H
#define IRENDERENGINE_H
#include <Public\IPlugin.h>
#include <Public\Colour.h>
#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\Renderer\IMesh.h>
#include <Public\Renderer\IRenderWindow.h>
#include <Public\BoundingBox.h>
#include <Public\BoundingSphere.h>

BEGIN_NAMESPACE

class IRenderTarget;
class ICamera;
class IRenderer;
class IMaterial;
class IPass;
class ITexture;
struct Matrix4;

class IRenderEngine : public IPlugin
{
	friend class Core;

protected:
	virtual ~IRenderEngine(void) {}

	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

	virtual void Initialize(void) = 0;

public:
	virtual IRenderWindow *CreateRenderWindow(const String &Text) = 0;
	virtual IRenderWindow *CreateRenderWindow(WindowUtility::WindowHandle WindowHandle) = 0;
	virtual void DestroyRenderWindow(IRenderWindow *Window) = 0;

	virtual void SetRenderTargetStage(uint8 Stage, IRenderTarget *Target) = 0;
	virtual void SetPass(IPass *Pass) = 0;
	virtual void SetTextureStage(uint8 Stage, ITexture *Texture) = 0;
	virtual void SetVertexDeclaration(VertexDeclarations Declaration) = 0;

	virtual void SetWorldMatrix(const Matrix4 &Matrix) = 0;
	virtual void SetViewMatrix(const Matrix4 &Matrix) = 0;
	virtual void SetProjectionMatrix(const Matrix4 &Matrix) = 0;

	virtual void DrawRenderer(IRenderer *Renderer) = 0;
	virtual void DrawMesh(const IMesh *Mesh) = 0;
	virtual void DrawIndexedTrianglesList(const Vertex *Vertices, uint32 VerticesCount, const void *Indices, uint32 TrianglesCount)
	{
		DrawVerticesList(Vertices, VerticesCount, VertexDeclarations::Standard, Indices, IndexDataAlignments::Bit16, TrianglesCount, PrimitiveTypes::Triangles);
	}
	virtual void DrawVerticesList(const Vertex *Vertices, uint32 VerticesCount, VertexDeclarations VertexDeclaration, const void *Indices, IndexDataAlignments IndexDataAlignment, uint32 PrimitivesCount, PrimitiveTypes PrimitiveType) = 0;

	virtual void DrawLine(const Vector3 &Start, const Vector3 &End, const Colour &Colour = Colour::WHITE) = 0;
	virtual void DrawPolygon(const Vector3 &Center, float32 Radius, uint32 VertexCount, const Colour &Colour)
	{
	}
	virtual void DrawPolygon(const List<Vector2> &Vertices, const Vector3 &Center, const Colour &Colour)
	{
		if (Vertices.GetSize() <= 1)
			return;

		Vector2 center = Vector2(Center.X, Center.Y);

		for (uint32 i = 0; i < Vertices.GetSize() - 1; i++)
			DrawLine(Vertices[i] + center, Vertices[i + 1] + center, Colour);
	}
	virtual void DrawPolygon(const Vector2 &Size, const Vector3 &Center, const Colour &Colour)
	{
		DrawLine(Vector2(Center.X - Size.X, Center.Y + Size.Y), Vector3(Center.X + Size.X, Center.Y + Size.Y, 0), Colour);
		DrawLine(Vector2(Center.X - Size.X, Center.Y - Size.Y), Vector3(Center.X + Size.X, Center.Y - Size.Y, 0), Colour);
		DrawLine(Vector2(Center.X - Size.X, Center.Y + Size.Y), Vector3(Center.X - Size.X, Center.Y - Size.Y, 0), Colour);
		DrawLine(Vector2(Center.X + Size.X, Center.Y + Size.Y), Vector3(Center.X + Size.X, Center.Y - Size.Y, 0), Colour);
	}
	virtual void DrawBoundingBox(const BoundingBox &BoundingBox, const Colour &Colour)
	{
		const Vector3 &min = BoundingBox.GetLowerCorner();
		const Vector3 &max = BoundingBox.GetUpperCorner();

		DrawLine(min, Vector3(max.X, min.Y, min.Z), Colour);
		DrawLine(min, Vector3(min.X, max.Y, min.Z), Colour);

		DrawLine(max, Vector3(min.X, max.Y, max.Z), Colour);
		DrawLine(max, Vector3(max.X, min.Y, max.Z), Colour);
	}

	virtual void Draw2DTexture(const ITexture *Texture, const Vector2 &Destination, bool UseTransparency = false, const Colour &Colour = Colour::WHITE) = 0;

	virtual const uint8 GetMaxSupportedRenderTargetsCount(void) const = 0;
	virtual const uint32 GetMaxSupportedPrimitivesCount(void) const = 0;
	virtual const uint8 GetMaxSupportedTexturesCount(void) const = 0;
};

END_NAMESPACE
#endif // IRENDERENGINE_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef RENDERERCOMMON_H
#define RENDERERCOMMON_H
#include <Public\Common.h>
#include <Public\Renderer\ITexture.h>
#include <Private\DirectXInclude.h>
#include <Public\Colour.h>

BEGIN_NAMESPACE

#define TO_Format(D3DFORMAT) \
	(D3DFORMAT == D3DFMT_X1R5G5B5 || D3DFORMAT == D3DFMT_A1R5G5B5 ? ColourFormats::A1R5G5B5 : \
	(D3DFORMAT == D3DFMT_A8B8G8R8 || D3DFORMAT == D3DFMT_A8R8G8B8 || D3DFORMAT == D3DFMT_X8R8G8B8 ? ColourFormats::A8R8G8B8 : \
	(D3DFORMAT == D3DFMT_R5G6B5 ? ColourFormats::R5G6B5 : \
	(D3DFORMAT == D3DFMT_R8G8B8 ? ColourFormats::R8G8B8 : \
	(D3DFORMAT == D3DFMT_R16F ? ColourFormats::R16F : \
	(D3DFORMAT == D3DFMT_G16R16F ? ColourFormats::G16R16F : \
	(D3DFORMAT == D3DFMT_A16B16G16R16F ? ColourFormats::A16B16G16R16F : \
	(D3DFORMAT == D3DFMT_R32F ? ColourFormats::R32F : \
	(D3DFORMAT == D3DFMT_G32R32F ? ColourFormats::G32R32F : \
	(D3DFORMAT == D3DFMT_A32B32G32R32F ? ColourFormats::A32B32G32R32F : ColourFormats::A1R5G5B5))))))))))

#define TO_D3DFORMAT(Format) \
	(Format == ColourFormats::A1R5G5B5 ? D3DFMT_A1R5G5B5 : \
	(Format == ColourFormats::A8R8G8B8 ? D3DFMT_A8R8G8B8 : \
	(Format == ColourFormats::R5G6B5 ? D3DFMT_R5G6B5 : \
	(Format == ColourFormats::R8G8B8 ? D3DFMT_R8G8B8 : \
	(Format == ColourFormats::R16F ? D3DFMT_R16F : \
	(Format == ColourFormats::G16R16F ? D3DFMT_G16R16F : \
	(Format == ColourFormats::A16B16G16R16F ? D3DFMT_A16B16G16R16F : \
	(Format == ColourFormats::R32F ? D3DFMT_R32F : \
	(Format == ColourFormats::G32R32F ? D3DFMT_G32R32F : \
	(Format == ColourFormats::A32B32G32R32F ? D3DFMT_A32B32G32R32F : D3DFMT_A1R5G5B5))))))))))

#define TO_FVF(Declaration) \
	(Declaration == VertexDeclarations::Standard ? D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEXCOORDSIZE2(0) : \
	(Declaration == VertexDeclarations::TwoTexCoords ? D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEXCOORDSIZE2(1) : 0))

#define GET_FVF_STRIDE(Declaration) \
	(Declaration == VertexDeclarations::Standard ? sizeof(Vertex) : \
	(Declaration == VertexDeclarations::TwoTexCoords ? sizeof(Vertex2Coords) : 0))

#define TO_FMT(Type) Type == IndexDataAlignments::Bit16 ? D3DFMT_INDEX16 : D3DFMT_INDEX32
#define GET_INDEX_STRIDE(Type) (Type == IndexDataAlignments::Bit16 ? sizeof(uint16) : sizeof(uint32))

#define TO_CMPFUNC(Function) \
	(Function == CompareFunctions::Less ? D3DCMP_LESSEQUAL : \
	(Function == CompareFunctions::Equal ? D3DCMP_EQUAL : \
	(Function == CompareFunctions::Less ? D3DCMP_LESS : \
	(Function == CompareFunctions::NotEqual ? D3DCMP_NOTEQUAL : \
	(Function == CompareFunctions::GreaterEqual ? D3DCMP_GREATEREQUAL : \
	(Function == CompareFunctions::Greater ? D3DCMP_GREATER : \
	(Function == CompareFunctions::Always ? D3DCMP_ALWAYS : D3DCMP_NEVER)))))))

#define TO_BLEND(Factor) \
	(Factor == BlendFactors::Zero ? D3DBLEND_ZERO : \
	(Factor == BlendFactors::One ? D3DBLEND_ONE : \
	(Factor == BlendFactors::DestinationColour ? D3DBLEND_DESTCOLOR : \
	(Factor == BlendFactors::OneMinusDestinationColour ? D3DBLEND_INVDESTCOLOR : \
	(Factor == BlendFactors::SourceColour ? D3DBLEND_SRCCOLOR : \
	(Factor == BlendFactors::OneMinusSourceColour ? D3DBLEND_INVSRCCOLOR : \
	(Factor == BlendFactors::SourceAlpha ? D3DBLEND_SRCALPHA : \
	(Factor == BlendFactors::OneMinusSourceAlpha ? D3DBLEND_INVSRCALPHA : \
	(Factor == BlendFactors::DestinationAlpha ? D3DBLEND_DESTALPHA : \
	(Factor == BlendFactors::OneMinusDestinationAlpha ? D3DBLEND_INVDESTALPHA : \
	(Factor == BlendFactors::SourceAlphaSaturate ? D3DBLEND_SRCALPHASAT : D3DBLEND_ZERO)))))))))))

END_NAMESPACE
#endif // RENDERERCOMMON_H

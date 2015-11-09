// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VERTEXGPUPROGRAM_H
#define VERTEXGPUPROGRAM_H

#include <Private\GPUProgram.h>

BEGIN_NAMESPACE

class VertexGPUProgram : public GPUProgram
{
public:
	VertexGPUProgram(const String &Source, const String &EntryPoint, const String &Type, const DefinesMap *Defines);
	virtual ~VertexGPUProgram(void);

	bool HasError(void) const
	{
		return !m_Shader;
	}

	INLINE IDirect3DVertexShader9 *GetShader(void) const
	{
		return m_Shader;
	}

private:
	IDirect3DVertexShader9 *m_Shader;
};

END_NAMESPACE
#endif // VERTEXGPUPROGRAM_H

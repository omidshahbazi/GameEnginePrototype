// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FRAGMENTGPUPROGRAM_H
#define FRAGMENTGPUPROGRAM_H

#include <Private\GPUProgram.h>

BEGIN_NAMESPACE

class FragmentGPUProgram : public GPUProgram
{
public:
	FragmentGPUProgram(const String &Source, const String &EntryPoint, const String &Type, const DefinesMap *Defines);
	virtual ~FragmentGPUProgram(void);

	bool HasError(void) const
	{
		return !m_Shader;
	}

	INLINE IDirect3DPixelShader9 *GetShader(void) const
	{
		return m_Shader;
	}

private:
	IDirect3DPixelShader9 *m_Shader;
};

END_NAMESPACE
#endif // FRAGMENTGPUPROGRAM_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\FragmentGPUProgram.h>
#include <Private\RenderEngine.h>
#include <Public\Core.h>
#include <Public\Renderer\IRenderEngine.h>

BEGIN_NAMESPACE


FragmentGPUProgram::FragmentGPUProgram(const String &Source, const String &EntryPoint, const String &Type, const DefinesMap *Defines) :
GPUProgram(Source, EntryPoint, Type, Defines),
m_Shader(NULL)
{
	static IDirect3DDevice9 *device = ((RenderEngine*)Core::GetReference().GetRenderer())->GetDevice();

	if (m_ShaderCode)
		device->CreatePixelShader((DWORD*)m_ShaderCode->GetBufferPointer(), &m_Shader);

	if (m_ShaderCode)
		m_ShaderCode->Release();
}


FragmentGPUProgram::~FragmentGPUProgram(void)
{
}


END_NAMESPACE

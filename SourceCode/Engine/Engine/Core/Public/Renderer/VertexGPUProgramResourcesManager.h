// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef VERTEXGPUPROGRAMRESOURCESMANAGER_H
#define VERTEXGPUPROGRAMRESOURCESMANAGER_H

#include <Public\Singleton.h>
#include <Public\Renderer\GPUProgramResourcesManager.h>

BEGIN_NAMESPACE

class CORE_API VertexGPUProgramResourcesManager : public GPUProgramResourcesManager
{
	DECLARE_SINGLETON(VertexGPUProgramResourcesManager)

private:
	VertexGPUProgramResourcesManager(void) {}

public:
	INLINE IGPUProgram *LoadProgram(const String &Name, const String &EntryPoint, VertexShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL)
	{
		IGPUProgram *prog = GetProgram(Name);

		if (prog)
			return prog;

		prog = m_Factory->LoadProgram(Name, EntryPoint, Type, Defines);

		if (prog)
			AddResource(Name, prog);

		return prog;
	}
	INLINE IGPUProgram *CreateProgram(const String &Name, const String &Source, const String &EntryPoint, VertexShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL)
	{
		if (HasResource(Name))
		{
			LOG_ERROR("There's already a GPUProgram named [" + Name + "]")

				return NULL;
		}

		IGPUProgram *prog = m_Factory->CreateProgram(Source, EntryPoint, Type, Defines);

		if (prog)
			AddResource(Name, prog);

		return prog;
	}
};

END_NAMESPACE
#endif // VERTEXGPUPROGRAMRESOURCESMANAGER_H

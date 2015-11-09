// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IGPUPROGRAMRESOURCESFACTORY_H
#define IGPUPROGRAMRESOURCESFACTORY_H

#include <Public\IResourcesFactory.h>
#include <Public\Renderer\IGPUProgram.h>

BEGIN_NAMESPACE

class IGPUProgramResourcesFactory : public IResourcesFactory
{
public:
	virtual ~IGPUProgramResourcesFactory(void) {}

	Resource *LoadResource(const String &Name) const
	{
		return NULL;
	}

	virtual IGPUProgram *LoadProgram(const String &Name, const String &EntryPoint, VertexShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const = 0;
	virtual IGPUProgram *LoadProgram(const String &Name, const String &EntryPoint, FragmentShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const = 0;

	virtual IGPUProgram *CreateProgram(const String &Source, const String &EntryPoint, VertexShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const = 0;
	virtual IGPUProgram *CreateProgram(const String &Source, const String &EntryPoint, FragmentShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const = 0;
};

END_NAMESPACE
#endif // IGPUPROGRAMRESOURCESFACTORY_H

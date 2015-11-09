// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GPUPROGRAM_H
#define GPUPROGRAM_H

#include <Public\Renderer\IGPUProgram.h>
#include <Public\Renderer\IGPUProgramUsage.h>
#include <Public\Renderer\GPUProgramResourcesManager.h>
#include <Private\DirectXInclude.h>

BEGIN_NAMESPACE

class GPUProgram : public IGPUProgram
{
public:
	GPUProgram(const String &Source, const String &EntryPoint, const String &Type, const IGPUProgram::DefinesMap *Defines);
	virtual ~GPUProgram(void);

	void SetConstantsToDefault(void);

	void SetConstant(const String &Name, const IGPUProgramUsage::Parameter &Constant);

protected:
	LPD3DXBUFFER m_ShaderCode;

private:
	typedef HashMap<String, D3DXHANDLE> ConstantsMap;

	LPD3DXCONSTANTTABLE m_ConstantsTable;
	ConstantsMap m_Constatnsts;
};

END_NAMESPACE
#endif // GPUPROGRAM_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GPUPROGRAMUSAGE_H
#define GPUPROGRAMUSAGE_H

#include <Public\Renderer\IGPUProgramUsage.h>
#include <Private\GPUProgram.h>

BEGIN_NAMESPACE

class GPUProgramUsage : public IGPUProgramUsage
{
public:
	typedef HashMap<String, String> AutoParamMap;

public:
	GPUProgramUsage(void) :
		m_Program(NULL)
	{
	}
	virtual ~GPUProgramUsage(void);

	void ClearAutoParams(void)
	{
		m_AutoParams.Clear();
	}
	void SetAutoParam(const String &Constant, const String &Param)
	{
		m_AutoParams[Constant] = Param;
	}

	void ClearParams(void)
	{
		m_Params.Clear();
	}
	void SetBool(const String &Name, bool Value)
	{
		m_Params[Name] = Value;
	}
	void SetInteger(const String &Name, int32 Value)
	{
		m_Params[Name] = Value;
	}
	void SetFloat(const String &Name, float32 Value)
	{
		m_Params[Name] = Value;
	}
	void SetVector2(const String &Name, const Vector2 &Value)
	{
		m_Params[Name] = Value;
	}
	void SetVector3(const String &Name, const Vector3 &Value)
	{
		m_Params[Name] = Value;
	}
	void SetColour(const String &Name, const Colour &Value)
	{
		m_Params[Name] = Value;
	}
	void SetMatrix(const String &Name, const Matrix4 &Value)
	{
		m_Params[Name] = Value;
	}

	void SetProgram(IGPUProgram *Program)
	{
		if (m_Program)
			m_Program->Drop();

		m_Program = (GPUProgram*)Program;

		if (m_Program)
			m_Program->Grab();
	}
	IGPUProgram *GetProgram(void) const
	{
		return m_Program;
	}

	bool HasProgram(void) const
	{
		return m_Program != NULL;
	}

	const ParamMap &GetParams(void) const
	{
		return m_Params;
	}

	const AutoParamMap &GetAutoParams(void) const
	{
		return m_AutoParams;
	}

private:
	GPUProgram *m_Program;
	AutoParamMap m_AutoParams;
	ParamMap m_Params;
};

END_NAMESPACE
#endif // GPUPROGRAMUSAGE_H

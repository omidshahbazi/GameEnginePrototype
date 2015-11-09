// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef GPUPROGRAMFACTORY_H
#define GPUPROGRAMFACTORY_H

#include <Public\Renderer\GPUParamDefinition.h>
#include <Public\Renderer\VertexGPUProgramResourcesManager.h>
#include <Public\Renderer\FragmentGPUProgramResourcesManager.h>
#include <Private\VertexGPUProgram.h>
#include <Private\FragmentGPUProgram.h>
#include <Private\JSONCPPInclude.h>
#include <Public\Enum.h>


BEGIN_NAMESPACE


const char *const VERTEX_SHADER_TYPE_NAMES[] = {
	"vs_1_1",
	"vs_2_0",
	"vs_2_a",
	"vs_3_0",
	"vs_4_0",
	"vs_4_1",
	"vs_5_0",
	NULL };


const char *const FRAGMET_SHADER_TYPE_NAMES[] = {
	"ps_1_1",
	"ps_1_2",
	"ps_1_3",
	"ps_1_4",
	"ps_2_0",
	"ps_2_a",
	"ps_2_b",
	"ps_3_0",
	"ps_4_0",
	"ps_4_1",
	"ps_5_0",
	NULL };


class GPUProgramResourcesFactory : public IGPUProgramResourcesFactory
{
private:
	IGPUProgram *LoadProgram(const String &Name, const String &EntryPoint, VertexShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const
	{
		return CreateProgram(FileIO::GetReference().ReadText(Core::GetReference().GetDataPath() + Name), EntryPoint, Type, Defines);
	}
	IGPUProgram *LoadProgram(const String &Name, const String &EntryPoint, FragmentShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const
	{
		return CreateProgram(FileIO::GetReference().ReadText(Core::GetReference().GetDataPath() + Name), EntryPoint, Type, Defines);
	}

	IGPUProgram *CreateProgram(const String &Source, const String &EntryPoint, VertexShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const
	{
		VertexGPUProgram *prog = new VertexGPUProgram(Source, EntryPoint, VERTEX_SHADER_TYPE_NAMES[(int32)Type], Defines);

		if (prog->HasError())
		{
			prog->Drop();
			return NULL;
		}

		return prog;
	}

	IGPUProgram *CreateProgram(const String &Source, const String &EntryPoint, FragmentShaderTypes Type, const IGPUProgram::DefinesMap *Defines = NULL) const
	{
		FragmentGPUProgram *prog = new FragmentGPUProgram(Source, EntryPoint, FRAGMET_SHADER_TYPE_NAMES[(int32)Type], Defines);

		if (prog->HasError())
		{
			prog->Drop();
			return NULL;
		}

		return prog;
	}

	const String &GetSupportedExtensions(void) const
	{
		static const String Supported_Extensions("hlsl");

		return Supported_Extensions;
	}

	bool IsExtensionSupported(const String &Extension) const
	{
		static const String Supported_Extensions("hlsl");

		return Supported_Extensions == Extension.ToLowerCase();
	}

public:
	static IGPUProgram *LoadGPUProgram(IGPUProgramUsage *Usage, Value ProgramValue, bool IsVertexProgram)
	{
		static VertexGPUProgramResourcesManager &vertexManager = VertexGPUProgramResourcesManager::GetReference();
		static FragmentGPUProgramResourcesManager &fragmentManager = FragmentGPUProgramResourcesManager::GetReference();

		if (ProgramValue == nullValue)
			return NULL;

		const Value fileName = ProgramValue.get("FileName", nullValue),
			entryPoint = ProgramValue.get("EntryPoint", "main"),
			typeValue = ProgramValue.get("Type", nullValue);

		if (fileName == nullValue)
		{
			//LOG_ERROR("In material [" + Material->GetName() + "::" + ProgramName + "] FileName doesn't supplied")
				return NULL;
		}
		else if (typeValue == nullValue)
		{
			//LOG_ERROR("In material [" + Material->GetName() + "::" + ProgramName + "] Type doesn't supplied")
				return NULL;
		}

		const Value packMatrix = ProgramValue.get("PackMatrixType", nullValue);
		const PackMatrixTypes oldPackMatrixType = GPUProgramResourcesManager::GetPackMatrixType();
		if (packMatrix != nullValue)
			GPUProgramResourcesManager::SetPackMatrixType(Enum::Parse<PackMatrixTypes>("PackMatrixTypes", packMatrix.asCString()));

		const Value optimizeType = ProgramValue.get("OptimizationType", nullValue);
		const OptimizationTypes oldOptimizeLevel = GPUProgramResourcesManager::GetOptimizationType();
		if (optimizeType != nullValue)
			GPUProgramResourcesManager::SetOptimizationType(Enum::Parse<OptimizationTypes>("OptimizationTypes", optimizeType.asCString()));

		const Value def = ProgramValue.get("Defines", nullValue);
		IGPUProgram::DefinesMap defines;
		if (def != nullValue)
		{
			const Value::Members members = def.getMemberNames();
			for (uint32 i = 0; i < members.size(); i++)
				defines[members[i].c_str()] = def.get(members[i], stringValue).asCString();
		}

		if (defines.GetSize())
			goto LoadProgram;

		IGPUProgram *program = IsVertexProgram ? vertexManager.GetProgram(fileName.asCString()) : fragmentManager.GetProgram(fileName.asCString());

		if (program)
			return program;

	LoadProgram:

		const String type(typeValue.asCString());

		if (IsVertexProgram)
		{
			if (!Enum::IsDefined("VertexShaderTypes", type))
			{
				LOG_ERROR("Type [" + type + "] doesn't exists in vertex shader types")

					goto Return;
			}

			program = vertexManager.LoadProgram(fileName.asCString(), entryPoint.asCString(), Enum::Parse<VertexShaderTypes>("VertexShaderTypes", type), &defines);
		}
		else
		{
			if (!Enum::IsDefined("FragmentShaderTypes", type))
			{
				LOG_ERROR("Type [" + type + "] doesn't exists in fragment shader types")

					goto Return;
			}

			program = fragmentManager.LoadProgram(fileName.asCString(), entryPoint.asCString(), Enum::Parse<FragmentShaderTypes>("FragmentShaderTypes", type), &defines);
		}

		if (program)
		{
			const Value autoPar = ProgramValue.get("AutoParam", nullValue);

			if (autoPar != nullValue)
			{
				const Value::Members members = autoPar.getMemberNames();
				for (uint32 i = 0; i < members.size(); i++)
				{
					std::string constant = members[i];

					const Value param = autoPar.get(constant, nullValue);

					if (param == nullValue)
						continue;

					Usage->SetAutoParam(constant.c_str(), param.asCString());
				}
			}

			const Value par = ProgramValue.get("Param", nullValue);

			if (par != nullValue)
			{
				const Value::Members members = par.getMemberNames();
				for (uint32 i = 0; i < members.size(); i++)
				{
					std::string constant = members[i];
					const Value param = par.get(constant, nullValue);

					if (param == "")
						continue;

					const String value(param.asCString());
					const StringsList list = value.Split(",");

					if (list.GetSize() == 1)
					{
						if (list[0].Find(".") != -1)
							Usage->SetFloat(constant.c_str(), StringConverter::ParseFloat32(value));
						else
							Usage->SetInteger(constant.c_str(), StringConverter::ParseInt32(value));
					}
					else if (list.GetSize() == 2)
						Usage->SetVector2(constant.c_str(), Vector2(StringConverter::ParseFloat32(list[0]), StringConverter::ParseFloat32(list[1])));
					else if (list.GetSize() == 3)
						Usage->SetVector3(constant.c_str(), Vector3(StringConverter::ParseFloat32(list[0]), StringConverter::ParseFloat32(list[1]), StringConverter::ParseFloat32(list[2])));
					else if (list.GetSize() == 4)
						Usage->SetColour(constant.c_str(), Colour(StringConverter::ParseUInt8(list[0]), StringConverter::ParseUInt8(list[1]), StringConverter::ParseUInt8(list[2]), StringConverter::ParseUInt8(list[3])));
				}
			}
		}

	Return:
		GPUProgramResourcesManager::SetPackMatrixType(oldPackMatrixType);
		GPUProgramResourcesManager::SetOptimizationType(oldOptimizeLevel);

		return program;

return NULL;
	}
};

END_NAMESPACE
#endif // GPUPROGRAMFACTORY_H

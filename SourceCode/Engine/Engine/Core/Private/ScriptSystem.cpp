// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\ScriptSystem.h>
#include <Public\Utility.h>
#include <Public\Core.h>
#include <Windows.h>
//#include "Public/VCPPProjectExporter.h"

//#define GENERATE_DEBUG_DATA

BEGIN_NAMESPACE

const String PROJECT_NAME("Scripts");
const String MSBUILD_PATH("\"%ProgramFiles(x86)%/MSBuild/12.0/Bin/MSBuild.exe\" ");


typedef Component* (*InstantiateComponet)(void);


int32 ExternalCall(const String &Command)
{
	return system(("\"" + Command + "\"").GetBuffer());
}


void GetALLFiles(StringsList &HeaderFiles, StringsList &CompileFiles, const String &Path)
{
	StringsList temp;
	Utility::GetFiles(temp, Path, true, ".h;.hpp;.c;.cpp");

	FOR_EACH(file, temp)
	{
		if (file->EndsWith(".h", true) || file->EndsWith(".hpp", true))
			HeaderFiles.Add(*file);
		else if (file->EndsWith(".c", true) || file->EndsWith(".cpp", true))
			CompileFiles.Add(*file);
	}

	temp = Utility::GetDirectories(Path);

	FOR_EACH(dir, temp)
		GetALLFiles(HeaderFiles, CompileFiles, Path + *dir);
}


DEFINE_SINGLETON(ScriptSystem)


ScriptSystem::ScriptSystem(void) :
m_Handle(NULL)
{
	Load();
}


void ScriptSystem::Recompile(void)
{
	/*StringsList headerFiles, compileFiles;
	GetALLFiles(headerFiles, compileFiles, Core::GetReference().GetDataPath());

	VCPPProjectExporter exp;
	exp.SetOutputDirectory("$(ProjectDir)");
	exp.SetTargetName("$(ProjectName)");
	exp.AddAdditionalIncludeDirectories("../Core/include/");
	exp.AddAdditionalLibraryDirectories("$(ProjectDir)");
	exp.AddAdditionalDependencies("Core.lib");
	exp.SetHeaderFiles(headerFiles);
	exp.SetCompileFiles(compileFiles);
	exp.SetToolsetVersion(ICPPProjectExporter::TV_12);
	exp.SetConfigurationType(ICPPProjectExporter::CT_DYNAMIC_LIBRARY);

#ifdef _DEBUG
	exp.SetGenerateDebugInfo(true);
	exp.SetBuildConfiguration(ICPPProjectExporter::BC_DEBUG);
	exp.SetRuntimeLibrary(ICPPProjectExporter::RL_MULTI_THREADED_DEBUG_DLL);
#else
	exp.SetGenerateDebugInfo(false);
	exp.SetBuildConfiguration(ICPPProjectExporter::BC_RELEASE);
	exp.SetRuntimeLibrary(ICPPProjectExporter::RL_MULTI_THREADED_DLL);
#endif

#ifdef _WIN32
	exp.SetPlatformType(ICPPProjectExporter::PT_WIN32);
#else
	exp.SetPlatformType(ICPPProjectExporter::PT_WIN64);
#endif

	const String projectPath = PROJECT_NAME + ".vcxproj";

	exp.Export(projectPath);

	Unload();

	int32 exitCode = ExternalCall(MSBUILD_PATH + "\"" + projectPath + "\" /p:configuration=debug");

	if (exitCode)
	{
		std::cout << "Error Code : " << exitCode << "\n";
		system("Pause");
	}

	Load();*/
}


Component *ScriptSystem::Instantiate(const String &ComponentType)
{
	if (m_Handle)
	{
		FARPROC proc = GetProcAddress((HMODULE)m_Handle, ("Instantiate" + ComponentType).GetBuffer());

		if (proc)
			return ((InstantiateComponet)proc)();
	}

	return NULL;
}


void ScriptSystem::Unload(void)
{
	if (m_Handle)
	{
		FreeResource((HGLOBAL)m_Handle);

		FreeLibrary((HMODULE)m_Handle);

		m_Handle = NULL;
	}
}


void ScriptSystem::Load(void)
{
	m_Handle = (int)LoadLibrary((PROJECT_NAME + ".dll").GetBuffer());
}

END_NAMESPACE

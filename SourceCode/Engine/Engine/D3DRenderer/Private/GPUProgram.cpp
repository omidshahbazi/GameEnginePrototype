// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\GPUProgram.h>
#include <Private\RenderEngine.h>
#include <Public\Core.h>
#include <Public\FileIO.h>

BEGIN_NAMESPACE

//class _OgreD3D9Export HLSLIncludeHandler : public ID3DXInclude
//{
//public:
//	HLSLIncludeHandler(Resource* sourceProgram)
//		: mProgram(sourceProgram) {}
//	~HLSLIncludeHandler() {}
//
//	STDMETHOD(Open)(D3DXINCLUDE_TYPE IncludeType,
//		LPCSTR pFileName,
//		LPCVOID pParentData,
//		LPCVOID *ppData,
//		uint32 *pByteLen
//		)
//	{
//		// find & load source code
//		DataStreamPtr stream =
//			ResourceGroupManager::getSingleton().openResource(
//			String(pFileName), mProgram->getGroup(), true, mProgram);
//
//		String source = stream->getAsString();
//		// copy into separate c-string
//		// Note - must NOT copy the null terminator, otherwise this will terminate
//		// the entire program string!
//		*pByteLen = static_cast<UINT>(source.length());
//		char* pChar = OGRE_ALLOC_T(char, *pByteLen, MEMCATEGORY_RESOURCE);
//		memcpy(pChar, source.c_str(), *pByteLen);
//		*ppData = pChar;
//
//		return S_OK;
//	}
//
//	STDMETHOD(Close)(LPCVOID pData)
//	{
//		OGRE_FREE(pData, MEMCATEGORY_RESOURCE);
//		return S_OK;
//	}
//protected:
//	Resource* mProgram;
//
//
//};

IDirect3DDevice9 *device = NULL;

GPUProgram::GPUProgram(const String &Source, const String &EntryPoint, const String &Type, const DefinesMap *Defines) :
m_ShaderCode(NULL),
m_ConstantsTable(NULL)
{
	if (!device)
		device = ((RenderEngine*)Core::GetReference().GetRenderer())->GetDevice();

	LPD3DXBUFFER error = NULL;

	Vector<D3DXMACRO> defines;

	const D3DXMACRO *defPointer = NULL;
	if (Defines != NULL && Defines->GetSize())
	{
		uint32 i = 0;
		FOR_EACH(key, *Defines)
		{
			D3DXMACRO macro;
			//macro.Name = String(*key).GetBuffer();
			//macro.Definition = String((*Defines)[*key]).GetBuffer();
			macro.Name = "DEV_BUILD";
			macro.Definition = NULL;
			defines.Add(macro);
		}

		D3DXMACRO macro;
		macro.Name = NULL;
		macro.Definition = NULL;
		defines.Add(macro);

		//defPointer = &defines[0];
	}

	int32 compileFlags = 0;

	switch (GPUProgramResourcesManager::GetPackMatrixType())
	{
	case PackMatrixTypes::ColumnMajor:
		ENABLE_FLAG(compileFlags, D3DXSHADER_PACKMATRIX_COLUMNMAJOR);
			break;

	case PackMatrixTypes::RowMajor:
		ENABLE_FLAG(compileFlags, D3DXSHADER_PACKMATRIX_ROWMAJOR);
			break;
	}

	switch (GPUProgramResourcesManager::GetOptimizationType())
	{
	case OptimizationTypes::None:
		ENABLE_FLAG(compileFlags, D3DXSHADER_SKIPOPTIMIZATION);
			break;

	case OptimizationTypes::Level0:
		ENABLE_FLAG(compileFlags, D3DXSHADER_OPTIMIZATION_LEVEL0);
			break;

	case OptimizationTypes::Level1:
		ENABLE_FLAG(compileFlags, D3DXSHADER_OPTIMIZATION_LEVEL1);
			break;

	case OptimizationTypes::Level2:
		ENABLE_FLAG(compileFlags, D3DXSHADER_OPTIMIZATION_LEVEL2);
			break;

	case OptimizationTypes::Level3:
		ENABLE_FLAG(compileFlags, D3DXSHADER_OPTIMIZATION_LEVEL3);
			break;
	}

	if (FAILED(D3DXCompileShader(Source.GetBuffer(), Source.GetLength(), defPointer, NULL, EntryPoint.GetBuffer(), Type.GetBuffer(), compileFlags, &m_ShaderCode, &error, &m_ConstantsTable)))
	{
		String msg = "Cannot compile shader "; // where's the name ? which shader ?, how user find-out which one has error ?

		if (error)
		{
			msg += (char*)error->GetBufferPointer();
			error->Release();
		}

		LOG_ERROR(msg)

			return;
	}

	D3DXCONSTANTTABLE_DESC tableDesc;
	m_ConstantsTable->GetDesc(&tableDesc);

	D3DXCONSTANT_DESC constDest;
	static uint32 count = 1;
	for (uint32 i = 0; i < tableDesc.Constants; i++)
	{
		D3DXHANDLE handle = m_ConstantsTable->GetConstant(NULL, i);

		m_ConstantsTable->GetConstantDesc(handle, &constDest, &count);

		if (constDest.Type == D3DXPT_FLOAT || constDest.Type == D3DXPT_INT || constDest.Type == D3DXPT_BOOL)
			m_Constatnsts[constDest.Name] = handle;
	}
}


GPUProgram::~GPUProgram(void)
{
}


void GPUProgram::SetConstantsToDefault(void)
{
	m_ConstantsTable->SetDefaults(device);
}


void GPUProgram::SetConstant(const String &Name, const IGPUProgramUsage::Parameter &Constant)
{
	ASSERTION(m_Constatnsts.ContainsKey(Name), "Constant [" + GetName() + "::" + Name + "] doesn't available in shader to set")

	uint32 count = Constant.GetCount();
	const void *data = Constant.GetData();

	D3DXHANDLE handle = m_Constatnsts[Name];

	switch (Constant.GetDataType())
	{
	case BasicDataTypes::Boolean:
		if (count > 1)
			m_ConstantsTable->SetBoolArray(device, handle, (BOOL*)data, count);
		else
			m_ConstantsTable->SetBool(device, handle, *(bool*)data);
		break;

	case BasicDataTypes::Integer:
		if (count > 1)
			m_ConstantsTable->SetIntArray(device, handle, (int*)data, count);
		else
			m_ConstantsTable->SetInt(device, handle, *(int*)data);
		break;

	case BasicDataTypes::Float:
		if (count > 1)
			m_ConstantsTable->SetFloatArray(device, handle, (float*)data, count);
		else
			m_ConstantsTable->SetFloat(device, handle, *(float*)data);
		break;
	}
}


END_NAMESPACE

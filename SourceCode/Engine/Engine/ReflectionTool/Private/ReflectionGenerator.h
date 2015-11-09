// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef REFLECTIONGENERATOR_H
#define REFLECTIONGENERATOR_H
#include <Private\ImplementDataStructureType.h>
#include <Private\ImplementEnumType.h>
#include <Private\ImplementPropertyType.h>
#include <Private\MetaDataStructure.h>
#include <Public\StringConverter.h>

BEGIN_NAMESPACE

class ReflectionGenerator
{
public:
	ReflectionGenerator(const String &FilePath, const String &OutputBaseFileName) :
		m_FilePath(FilePath),
		m_OutputBaseFileName(OutputBaseFileName)
	{
	}

	bool Generate(void);

private:
	void GenerateHeaderFile(String &HeaderContent, const Type::TypesList &Types);
	void GenerateCompileFile(String &CompileContent, const Type::TypesList &Types);
	void GenerateDataStructuresDefinition(String &RootContent, String &Content, String &FunctionsDefinition, const Type::TypesList &Types, AccessSpecifiers Access);
	void GenerateConstructorsDefinition(String &Content, const Type::TypesList &Types, AccessSpecifiers Access);
	void GenerateFunctionsDefinition(String &Content, const Type::TypesList &Types, AccessSpecifiers Access);
	void GenerateVariablesDefinition(String &Content, const Type::TypesList &Types, AccessSpecifiers Access);

	static String GetPointerName(Type *Type)
	{
		return (Type->GetType() == Type::Types::DataStructure ? ((MetaDataStructure*)Type)->GetUniqueName() : Type->GetName()) + "Ptr";
	}

	static String GetAccessText(AccessSpecifiers Access)
	{
		return (Access == AccessSpecifiers::Public ? "Public" : "Private");
	}

	INLINE static String GetArgumentsText(const Parameter::ParametersList &Parameters)
	{
		String ret;

		if (Parameters.GetSize() != 0)
		{
			for (uint8 i = 0; i < Parameters.GetSize(); i++)
			{
				const Parameter &param = Parameters[i];

				ret += GetArgumentText(i, param.GetDataType());

				if (i < Parameters.GetSize() - 1)
					ret += ",";
			}
		}

		return ret;
	}

	INLINE static String GetArgumentText(int32 Index, const DataType &Type)
	{
		String ret;

		if (Type.GetValueType() == ValueTypes::None)
			if (Type.GetPassType() == DataType::PassesTypes::Pointer)
				ret += "(" + Type.GetExtraValueType() + "*)";

		ret += "(*Arguments)[" + StringConverter::ToString(Index) + "].GetAs";

		if (Type.GetPassType() == DataType::PassesTypes::Pointer)
			ret += GetValueTypeText(ValueTypes::Void);
		else
			ret += GetValueTypeText(Type.GetValueType(), false);

		ret += "()";

		return ret;
	}

	INLINE static String GetValueTypeText(ValueTypes Type, bool WithPrefix = false)
	{
		String ret = (WithPrefix ? "ValueTypes::" : "");

		switch (Type)
		{
			//case ValueTypes::None:
			//	ret += "None";
			//	break;

		case ValueTypes::Void:
			ret += "Void";
			break;

		case ValueTypes::Bool:
			ret += "Bool";
			break;

		case ValueTypes::UInt8:
			ret += "UInt8";
			break;
		case ValueTypes::UInt16:
			ret += "UInt16";
			break;
		case ValueTypes::UInt32:
			ret += "UInt32";
			break;
		case ValueTypes::UInt64:
			ret += "UInt64";
			break;

		case ValueTypes::Int8:
			ret += "Int8";
			break;
		case ValueTypes::Int16:
			ret += "Int16";
			break;
		case ValueTypes::Int32:
			ret += "Int32";
			break;
		case ValueTypes::Int64:
			ret += "Int64";
			break;

		case ValueTypes::Float32:
			ret += "Float32";
			break;
		case ValueTypes::Float64:
			ret += "Float64";
			break;

		case ValueTypes::Double32:
			ret += "Double32";
			break;
		case ValueTypes::Double64:
			ret += "Double64";
			break;

		case ValueTypes::String:
			ret += "String";
			break;
		case ValueTypes::Vector2:
			ret += "Vector2";
			break;
		case ValueTypes::Vector3:
			ret += "Vector3";
			break;
		case ValueTypes::Matrix4:
			ret += "Matrix4";
			break;
		}

		return ret;
	}

private:
	String m_FilePath;
	String m_OutputBaseFileName;
	String m_OutputClassName;
};

END_NAMESPACE
#endif // REFLECTIONGENERATOR_H

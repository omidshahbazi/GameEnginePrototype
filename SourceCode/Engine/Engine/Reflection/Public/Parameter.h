// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef PARAMETER_H
#define PARAMETER_H
#include <Public\DataType.h>
#include <Public\AnyDataType.h>

BEGIN_NAMESPACE

class Parameter
{
public:
	typedef Vector<Parameter> ParametersList;

public:
	Parameter(const DataType &DataType, const String &Name) :
		m_DataType(DataType),
		m_Name(Name)
	{
	}

	INLINE const DataType &GetDataType(void) const
	{
		return m_DataType;
	}

	INLINE void GetSignature(String &Signature) const
	{
		m_DataType.GetSignature(Signature);
	}

private:
	DataType m_DataType;
	String m_Name;
};

END_NAMESPACE

#endif // PARAMETER_H

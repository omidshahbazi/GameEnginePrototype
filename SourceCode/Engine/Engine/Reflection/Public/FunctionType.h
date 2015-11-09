// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef FUNCTIONTYPE_H
#define FUNCTIONTYPE_H
#include <Public\Type.h>
#include <Public\Parameter.h>

BEGIN_NAMESPACE

class REFLECTION_API FunctionType : public Type
{
public:
	FunctionType(Type *TopNest) :
		Type(TopNest),
		m_IsConst(false)
	{
	}
	virtual ~FunctionType(void)
	{
	}

	INLINE Types GetType(void) const
	{
		return Types::Function;
	}

	INLINE const DataType &GetReturnType(void) const
	{
		return m_ReturnType;
	}

	INLINE const Parameter::ParametersList &GetParameters(void) const
	{
		return m_Parameters;
	}

	INLINE bool GetIsConst(void) const
	{
		return m_IsConst;
	}

	AnyDataType Invoke(void *TargetObject) const;
	AnyDataType Invoke(void *TargetObject, const AnyDataType &Argument) const;
	AnyDataType Invoke(void *TargetObject, const ArgumentsList &Arguments) const;

protected:
	virtual void InvokeInternal(void *TargetObject, AnyDataType &ReturnValue, const ArgumentsList *Arguments) const = 0;

protected:
	DataType m_ReturnType;
	Parameter::ParametersList m_Parameters;
	bool m_IsConst;
};

END_NAMESPACE

#endif // FUNCTIONTYPE_H

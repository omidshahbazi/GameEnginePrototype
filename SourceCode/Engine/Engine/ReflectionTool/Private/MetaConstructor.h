// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef METACONSTRUCTOR_H
#define METACONSTRUCTOR_H
#include <Public\Type.h>
#include <Public\Parameter.h>

BEGIN_NAMESPACE

class MetaConstructor : public Type
{
public:
	MetaConstructor(Type *TopNest) :
		Type(TopNest)
	{
	}
	~MetaConstructor(void)
	{
	}

	INLINE Types GetType(void) const
	{
		return Types::Constructor;
	}

	INLINE void SetName(const String &Value)
	{
		m_Name = Value;
	}

	INLINE void AddParameter(const DataType &DataType, const String &Name)
	{
		m_Parameters.Add(Parameter(DataType, Name));
	}

	INLINE const Parameter::ParametersList &GetParameters(void) const
	{
		return m_Parameters;
	}

	void Invoke(void *TargetObject) const;
	void Invoke(void *TargetObject, const AnyDataType &Argument) const;
	void Invoke(void *TargetObject, const ArgumentsList &Arguments) const;

protected:
	virtual void InvokeInternal(void *TargetObject, const ArgumentsList *Arguments) const
	{

	}

protected:
	Parameter::ParametersList m_Parameters;
};

END_NAMESPACE
#endif // METACONSTRUCTOR_H

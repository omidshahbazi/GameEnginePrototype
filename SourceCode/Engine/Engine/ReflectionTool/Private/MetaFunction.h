// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef METAFUNCTION_H
#define METAFUNCTION_H
#include <Private\ImplementFunctionType.h>
#include <Private\Specifiers.h>

BEGIN_NAMESPACE

class MetaFunction : public ImplementFunctionType, public Specifiers
{
public:
	MetaFunction(Type *TopNest) :
		ImplementFunctionType(TopNest)
	{
	}
	~MetaFunction(void)
	{
	}

	INLINE void GetSignature(String &Signature, String &SignatureName) const
	{
		m_ReturnType.GetSignature(Signature);

		SignatureName = m_Name + "Signature";

		Signature += "(" + m_TopNest->GetScopedName() + "::*" + SignatureName + ")";

		Signature += "(";

		for (uint32 i = 0; i < m_Parameters.GetSize(); i++)
		{
			const Parameter &param = m_Parameters[i];
			param.GetSignature(Signature);

			if (i < m_Parameters.GetSize() - 1)
				Signature += ", ";
		}

		Signature += ")";

		if (m_IsConst)
			Signature += " const";
	}

	INLINE String GetUniqueName(void) const
	{
		return (m_TopNest->GetName() + "_") + m_Name;
	}

protected:
	void InvokeInternal(void *TargetObject, AnyDataType &ReturnValue, const ArgumentsList *Argumetns) const
	{
	}
};

END_NAMESPACE
#endif // METAFUNCTION_H

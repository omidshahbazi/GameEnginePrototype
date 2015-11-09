// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SPECIFIERS_H
#define SPECIFIERS_H

#include <public\Common.h>

BEGIN_NAMESPACE

class Specifiers
{
public:
	void AddSpecifier(const String &Value)
	{
		m_Specifiers.Add(Value);
	}

	const StringsList &GetSpecifiers(void) const
	{
		return m_Specifiers;
	}

private:
	StringsList m_Specifiers;

};

END_NAMESPACE

#endif // SPECIFIERS_H

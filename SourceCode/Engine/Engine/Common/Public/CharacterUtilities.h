// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CHARACTERUTILITIES_H
#define CHARACTERUTILITIES_H

#include <Public\SecondaryCommon.h>

BEGIN_NAMESPACE

class COMMON_API CharacterUtilities
{
public:
	template <class T> static INLINE T ToLowerCase(T C)
	{
		return (C >= 'A' && C <= 'Z' ? C + 0x20 : C);
	}
	template <class T> static INLINE T ToUpperCase(T C)
	{
		return (C >= 'a' && C <= 'z' ? C - 0x20 : C);
	}
};

END_NAMESPACE
#endif // CHARACTERUTILITIES_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef CALLOCATIONPOLICY_H
#define CALLOCATIONPOLICY_H

#include <Public\SecondaryCommon.h>
#include <Public\Singleton.h>

BEGIN_NAMESPACE

class COMMON_API CAllocationPolicy
{
	DECLARE_SINGLETON(CAllocationPolicy)

private:
	CAllocationPolicy(void) {}

public:
#if _DEBUG
	static void *Allocate(uint32 Size, uint32 Count, const char *File, int32 Line);
	static void Deallocate(void *Block, const char *File, int32 Line);
#else
	static void *Allocate(uint32 Size, uint32 Count = 1);
	static void Deallocate(void *Block);
#endif
};


END_NAMESPACE
#endif // CALLOCATIONPOLICY_H

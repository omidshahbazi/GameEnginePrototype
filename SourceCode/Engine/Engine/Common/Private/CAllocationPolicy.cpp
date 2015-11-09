// Copyright 2012-2015 ?????????????. All Rights Reserved.

#include <Public\CAllocationPolicy.h>
#include <memory>

BEGIN_NAMESPACE

DEFINE_SINGLETON(CAllocationPolicy)

#if _DEBUG
void *CAllocationPolicy::Allocate(uint32 Size, uint32 Count, const char *File, int32 Line)
#else
void *CAllocationPolicy::Allocate(uint32 Size, uint32 Count)
#endif
{
	return malloc(Size * Count);
}


#if _DEBUG
void CAllocationPolicy::Deallocate(void *Block, const char *File, int32 Line)
#else
void CAllocationPolicy::Deallocate(void *Block)
#endif
{
	free(Block);
}

END_NAMESPACE

// Copyright 2012-2015 ?????????????. All Rights Reserved.

#include <Public\SmallObjectAllocationPolicy.h>

BEGIN_NAMESPACE

#define TOTAL_SIZE 512

DEFINE_SINGLETON(SmallObjectAllocationPolicy)


SmallObjectAllocationPolicy::SmallObjectAllocationPolicy(void) :
AllocationPolicy(TOTAL_SIZE)
{
}


#ifdef _DEBUG
void *SmallObjectAllocationPolicy::Allocate(uint32 Size, uint32 Count, const char *File, int32 Line)
#else
void *SmallObjectAllocationPolicy::Allocate(uint32 Size, uint32 Count)
#endif
{
	static AllocationPolicy *alloc = (AllocationPolicy*)SmallObjectAllocationPolicy::GetPointer();

#ifdef _DEBUG
	return alloc->Allocate(Size, Count, File, Line);
#else
	return alloc->Allocate(Size, Count);
#endif
}


#ifdef _DEBUG
void SmallObjectAllocationPolicy::Deallocate(void *Block, const char *File, int32 Line)
#else
void SmallObjectAllocationPolicy::Deallocate(void *Block)
#endif
{
	static AllocationPolicy *alloc = (AllocationPolicy*)SmallObjectAllocationPolicy::GetPointer();

#ifdef _DEBUG
	return alloc->Deallocate(Block, File, Line);
#else
	return alloc->Deallocate(Block);
#endif
}


END_NAMESPACE

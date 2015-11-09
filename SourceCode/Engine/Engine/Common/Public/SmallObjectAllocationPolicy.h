// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SMALLOBJECTALLOCATIONPOLICY_H
#define SMALLOBJECTALLOCATIONPOLICY_H

#include <Public\AllocationPolicy.h>

BEGIN_NAMESPACE

class COMMON_API SmallObjectAllocationPolicy : protected AllocationPolicy
{
	DECLARE_SINGLETON(SmallObjectAllocationPolicy)

private:
	SmallObjectAllocationPolicy(void);

public:
#ifdef _DEBUG
	static void *Allocate(uint32 Size, uint32 Count, const char *File, int32 Line);
	static void Deallocate(void *Block, const char *File, int32 Line);
#else
	static void *Allocate(uint32 Size, uint32 Count);
	static void Deallocate(void *Block);
#endif
};


END_NAMESPACE
#endif // SMALLOBJECTALLOCATIONPOLICY_H

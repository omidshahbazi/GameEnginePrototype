// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SCENEALLOCATIONPOLICY_H
#define SCENEALLOCATIONPOLICY_H

#include <Public\AllocationPolicy.h>

BEGIN_NAMESPACE

class CORE_API SceneAllocationPolicy : protected AllocationPolicy
{
	DECLARE_SINGLETON(SceneAllocationPolicy)

private:
	SceneAllocationPolicy(void);

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
#endif // SCENEALLOCATIONPOLICY_H

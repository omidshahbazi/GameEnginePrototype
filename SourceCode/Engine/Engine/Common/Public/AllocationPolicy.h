// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ALLOCATIONPOLICY_H
#define ALLOCATIONPOLICY_H

#include <Public\SecondaryCommon.h>
#include <Public\Singleton.h>

BEGIN_NAMESPACE

class COMMON_API AllocationPolicy
{
public:
	AllocationPolicy(uint32 ReserveSize);

public:
#ifdef _DEBUG
	void *Allocate(uint32 Size, uint32 Count, const char *File, int32 Line);
	void Deallocate(void *Block, const char *File, int32 Line);
#else
	void *Allocate(uint32 Size, uint32 Count);
	void Deallocate(void *Block);
#endif

private:
	uint8 *m_Memory;
	uint8 *m_EndOfMemory;
	uint8 *m_FirstAvailable;
};


#ifdef FILE_LINE
#undef FILE_LINE
#endif
#if _DEBUG
#define FILE_LINE , __FILE__, __LINE__
#else
#define FILE_LINE
#endif


END_NAMESPACE
#endif // ALLOCATIONPOLICY_H

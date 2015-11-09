// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <Public\SecondaryCommon.h>

BEGIN_NAMESPACE

template<class AP> class Allocator
{
public:
	void *operator new(uint32 Size)
	{
		return AP::Allocate(Size, 1 FILE_LINE);
	}
	void *operator new [](uint32 Size)
	{
		return NULL;
//		return AP::Allocate(Size, 1 FILE_LINE);
	}

	void operator delete(void *Block)
	{
		return AP::Deallocate(Block FILE_LINE);
	}
	void operator delete[](void *Block)
	{
		return AP::Deallocate(Block FILE_LINE);
	}
};

END_NAMESPACE
#endif // ALLOCATOR_H

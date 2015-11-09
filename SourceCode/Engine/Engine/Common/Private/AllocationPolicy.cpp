// Copyright 2012-2015 ?????????????. All Rights Reserved.
#pragma once
//#pragma pack(1) // for pack size of Header

#include <Public\AllocationPolicy.h>
#include <Public\Common.h>
#include <memory>
#include <assert.h>

BEGIN_NAMESPACE

//#define WITH_DEBUG_INFO
#ifndef _DEBUG
#undef WITH_DEBUG_INFO
#endif


class Header
{
public:
	uint32 Size;
	Header *NextAvailable;

#ifdef WITH_DEBUG_INFO
	char *File;
	int32 Line;
#endif
};


const uint8 HEADER_SIZE = sizeof(Header);
const uint8 SEPERATION_SIZE = HEADER_SIZE + 4;


AllocationPolicy::AllocationPolicy(uint32 ReserveSize) :
m_Memory(NULL),
m_EndOfMemory(NULL),
m_FirstAvailable(NULL)
{
	const uint32 totalBytesCount = ReserveSize * 1048576;

	m_Memory = m_FirstAvailable = (uint8*)malloc(totalBytesCount);
	m_EndOfMemory = m_Memory ? m_Memory + totalBytesCount : NULL;

	assert(m_Memory && "Reserving memory failed");

	memset(m_Memory, 0, totalBytesCount);

	Header *header = (Header*)m_Memory;
	header->Size = totalBytesCount - HEADER_SIZE;
#ifdef WITH_DEBUG_INFO
	header->File = NULL;
	header->Line = 0;
#endif
}


#ifdef _DEBUG
void *AllocationPolicy::Allocate(uint32 Size, uint32 Count, const char *File, int32 Line)
#else
void *AllocationPolicy::Allocate(uint32 Size, uint32 Count)
#endif
{
	const uint32 desireDataSize = (Size * Count);

	assert(Size && Count && "Size and Count must be non-zero");

	Header *header = (Header*)m_FirstAvailable,
		*prevHeader = NULL;

	while (header && (uint8*)header < m_EndOfMemory)
	{
		if (header->Size >= desireDataSize)
		{
			if (header->Size - desireDataSize >= SEPERATION_SIZE)
			{
				Header *sepHeader = (Header*)header + HEADER_SIZE + desireDataSize;
				sepHeader->Size = header->Size - (desireDataSize + HEADER_SIZE);
				assert(sepHeader->Size && "Size must be non-zero");
				sepHeader->NextAvailable = NULL;

#ifdef WITH_DEBUG_INFO
				sepHeader->File = NULL;
				sepHeader->Line = 0;
#endif

				//sepHeader->NextAvailable = (Header*)m_FirstAvailable;
				//m_FirstAvailable = (uint8*)sepHeader;

				Header *firstAvailable = (Header*)m_FirstAvailable;

				if (firstAvailable + HEADER_SIZE + firstAvailable->Size == sepHeader)
					firstAvailable->Size += HEADER_SIZE + sepHeader->Size;
				else if (sepHeader + HEADER_SIZE + sepHeader->Size == firstAvailable)
				{
					sepHeader->Size += HEADER_SIZE + firstAvailable->Size;
					m_FirstAvailable = (uint8*)sepHeader;
				}
				else
				{
					sepHeader->NextAvailable = firstAvailable;
					m_FirstAvailable = (uint8*)sepHeader;
				}

				header->Size = desireDataSize;
				assert(header->Size && "Size must be non-zero");
			}

			if (m_FirstAvailable == (uint8*)header)
				m_FirstAvailable = (uint8*)header->NextAvailable;

			if (prevHeader)
				prevHeader->NextAvailable = header->NextAvailable;

#ifdef WITH_DEBUG_INFO
			uint32 len = strlen(File) + 1;
			header->File = new char[len];
			memcpy(header->File, File, len);
			header->Line = Line;
#endif

			return header + HEADER_SIZE;
		}

		prevHeader = header;
		header = header->NextAvailable;
	}

	assert(!"There's no enough byte(s) to allocate");

	return NULL;
}


#ifdef _DEBUG
void AllocationPolicy::Deallocate(void *Block, const char *File, int32 Line)
#else
void AllocationPolicy::Deallocate(void *Block)
#endif
{
	if (!Block)
		return;

	assert(Block >= m_Memory && Block < m_EndOfMemory && "Block should be in range of reserved memory");

	//Header *header = (Header*)((uint8*)Block - HEADER_SIZE);
	//header->NextAvailable = (Header*)m_FirstAvailable;
	//m_FirstAvailable = (uint8*)header;

	Header *firstAvailable = (Header*)m_FirstAvailable;
	Header *header = (Header*)((uint8*)Block - HEADER_SIZE);

	if (firstAvailable + HEADER_SIZE + firstAvailable->Size == header)
		firstAvailable->Size += HEADER_SIZE + header->Size;
	else if (header + HEADER_SIZE + header->Size == firstAvailable)
	{
		header->Size += HEADER_SIZE + firstAvailable->Size;
		m_FirstAvailable = (uint8*)header;
	}
	else
	{
		header->NextAvailable = firstAvailable;
		m_FirstAvailable = (uint8*)header;
	}
}


END_NAMESPACE

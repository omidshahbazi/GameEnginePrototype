// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef REFERENCECOUNTED_H
#define REFERENCECOUNTED_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class COMMON_API ReferenceCounted
{
public:
	ReferenceCounted(void);
	virtual ~ReferenceCounted(void)
	{
		ASSERTION(m_Count <= 1, "Deleting object what has references to somewhere")
	}

	INLINE void Grab(void)
	{
		m_Count++;
	}

	INLINE void Drop(void)
	{
		if (--m_Count == 0)
			delete this;
	}

private:
	uint32 m_Count;
};

END_NAMESPACE
#endif // REFERENCECOUNTED_H

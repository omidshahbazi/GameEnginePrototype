// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef ANDROIDSYSTEM_H
#define ANDROIDSYSTEM_H

#include <Public\Common.h>

BEGIN_NAMESPACE

class CORE_API AndroidSystem
{
	DECLARE_SINGLETON(AndroidSystem)

private:
	AndroidSystem(void);
	~AndroidSystem(void);

public:
	void Export(void);
};

END_NAMESPACE
#endif // ANDROIDSYSTEM_H

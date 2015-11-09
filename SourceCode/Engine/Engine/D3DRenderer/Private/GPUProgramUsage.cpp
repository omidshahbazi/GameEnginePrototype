// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\GPUProgramUsage.h>

BEGIN_NAMESPACE


GPUProgramUsage::~GPUProgramUsage(void)
{
	if (m_Program)
		m_Program->Drop();
}


END_NAMESPACE

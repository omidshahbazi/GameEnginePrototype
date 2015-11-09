// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\MaterialAPI.h>

BEGIN_NAMESPACE


IPass *Material_CreatePass(IMaterial *Material)
{
	return Material->CreatePass();
}


uint8 Material_GetPassesCount(IMaterial *Material)
{
	return Material->GetPasses().GetSize();
}


IPass *Material_GetPass(IMaterial *Material, uint8 Index)
{
	return Material->GetPass(Index);
}


END_NAMESPACE

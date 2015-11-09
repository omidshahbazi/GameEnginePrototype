// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\CompositeAPI.h>

BEGIN_NAMESPACE


ICompositePass *Material_CreatePass(IComposite *Composite)
{
	return Composite->CreatePass();
}


uint8 Material_GetPassesCount(IComposite *Composite)
{
	return Composite->GetPasses().GetSize();
}


ICompositePass *Material_GetPass(IComposite *Composite, uint8 Index)
{
	return Composite->GetPass(Index);
}


END_NAMESPACE

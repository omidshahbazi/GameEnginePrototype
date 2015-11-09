// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef COMPOSITEAPI_H
#define COMPOSITEAPI_H
#include <Public\Utilities.h>
#include <Public\IComposite.h>

BEGIN_NAMESPACE

API_FUNCTION ICompositePass *Composite_CreatePass(IComposite *Composite);
API_FUNCTION uint8 Composite_GetPassesCount(IComposite *Composite);
API_FUNCTION ICompositePass *Composite_GetPass(IComposite *Composite, uint8 Index);

END_NAMESPACE
#endif // COMPOSITEAPI_H

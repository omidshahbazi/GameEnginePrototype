// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MATERIALAPI_H
#define MATERIALAPI_H
#include <Public\Utilities.h>
#include <Public\IMaterial.h>

BEGIN_NAMESPACE

API_FUNCTION IPass *Material_CreatePass(IMaterial *Material);
API_FUNCTION uint8 Material_GetPassesCount(IMaterial *Material);
API_FUNCTION IPass *Material_GetPass(IMaterial *Material, uint8 Index);

END_NAMESPACE
#endif // MATERIALAPI_H

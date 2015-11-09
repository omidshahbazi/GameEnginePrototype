// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Type.h>

BEGIN_NAMESPACE

Type::Type(const String &Name) :
m_TypeID((uint32)this),
m_Name(Name),
m_TopNest(NULL)
{
}


Type::Type(Type *TopNest) :
m_TypeID((uint32)this),
m_TopNest(TopNest)
{
}


Type::Type(const String &Name, Type *TopNest) :
m_TypeID((uint32)this),
m_Name(Name),
m_TopNest(TopNest)
{
}

END_NAMESPACE

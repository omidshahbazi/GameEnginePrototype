// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\Material.h>
#include <Private\Pass.h>
#include <Public\Core.h>
#include <Public\Utility.h>
#include <Public\FileIO.h>
#include <Public\Renderer\IRenderEngine.h>

BEGIN_NAMESPACE

//Material::Material(void)
//{
//}
//
//
//Material::~Material(void)
//{
//}


IPass *Material::CreatePass(void)
{
	Pass *pass = new Pass;

	m_Passes.Add(pass);

	return pass;
}


END_NAMESPACE

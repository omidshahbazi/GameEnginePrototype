// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MATERIAL_H
#define MATERIAL_H

#include <Public\Renderer\IMaterial.h>

BEGIN_NAMESPACE

class Material : public IMaterial
{
public:
	//Material(void);
	//~Material(void);

	IPass *CreatePass(void);

	IPass *GetPass(uint8 Index) const
	{
		return m_Passes[Index];
	}

	const PassesList &GetPasses(void) const
	{
		return m_Passes;
	}

private:
	void Load(void);

private:
	PassesList m_Passes;
};

END_NAMESPACE
#endif // MATERIAL_H

// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef STATISTICS_H
#define STATISTICS_H
#ifdef _DEBUG


#include <Public\Common.h>
#include <Public\Singleton.h>
//#include "Public/GUISystem/IGUIScene.h"

BEGIN_NAMESPACE

class Core;

class Statistics
{
	DECLARE_SINGLETON(Statistics)

private:
	Statistics(void);
	~Statistics(void);

public:
	void Update(void);
	void Render(void);

private:
	Core *m_Core;
	//IGUIScene *m_GUIScene;
	//ILabel *m_Statistics;
};

END_NAMESPACE

#endif
#endif // STATISTICS_H

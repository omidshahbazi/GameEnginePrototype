// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef IMOVIEMANAGER_H
#define IMOVIEMANAGER_H

#include <Public\Renderer\IMovie.h>

BEGIN_NAMESPACE
	
//<Description>
//This is sample description
class IMovieManager
{
public:
	virtual ~IMovieManager(void) {}

	virtual void Update(void) = 0;

	virtual IMovie *LoadMovie(const String &RelativeFilePath) = 0;
	virtual void DestroyMovie(IMovie *Movie) = 0;
};

END_NAMESPACE
#endif // IMOVIEMANAGER_H

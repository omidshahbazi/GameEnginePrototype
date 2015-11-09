// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MOVIEMANAGER_H
#define MOVIEMANAGER_H

#include <Public\Renderer\IMovieManager.h>

BEGIN_NAMESPACE

class MovieManager : public IMovieManager
{
public:
	MovieManager(void);
	~MovieManager(void);

	void Update(void);

	IMovie *LoadMovie(const String &RelativeFilePath);
	void DestroyMovie(IMovie *Movie);

private:
	typedef Vector<IMovie*> MovieList;

	MovieList m_Movies;
};

END_NAMESPACE
#endif // MOVIEMANAGER_H

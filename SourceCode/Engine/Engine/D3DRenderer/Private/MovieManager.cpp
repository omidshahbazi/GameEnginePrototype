// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Private\MovieManager.h>
#include <Public\Core.h>
#include <Private\Movie.h>

BEGIN_NAMESPACE

MovieManager::MovieManager(void)
{
}


MovieManager::~MovieManager(void)
{
	FOR_EACH(movie, m_Movies)
		delete &movie;

	LOG_INFO_DEBUG("IMovieManager destoryed successfully")
}


void MovieManager::Update(void)
{
	FOR_EACH(movie, m_Movies)
		movie->Update();
}


IMovie *MovieManager::LoadMovie(const String &RelativeFilePath)
{
	Movie *movie = new Movie(RelativeFilePath);

	m_Movies.Add(movie);

	return movie;
}


void MovieManager::DestroyMovie(IMovie *Movie)
{
	if (!Movie)
		return;

	m_Movies.Remove(Movie);

	delete Movie;
}

END_NAMESPACE

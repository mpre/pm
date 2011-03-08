#include "GameCache.h"


GameCache::GameCache(void)
{
}


GameCache::~GameCache(void)
{
	/*SurfaceList::iterator i = m_sList.begin();
	SurfaceList::iterator end = m_sList.end();

	while(i!=end)
	{
		SDL_FreeSurface(i->second.get());
		++i;
	}*/

	m_sList.clear();
}


void GameCache::Init(void)
{
	loadOptimized( "img/player2.png", PPLAYER );
	loadOptimized( "img/terrain_tile.png", TERRAIN_TILE );
	loadOptimized( "img/spike.png", PSPIKE_UP);
}

bool GameCache::loadOptimized(string path, int position)
{
	SDL_Surface* loadedS = IMG_Load( path.c_str() );
	if ( loadedS != NULL )
	{
		SDL_Surface* optimizedS = SDL_DisplayFormat(loadedS);
		if( optimizedS != NULL )
		{
			SDL_FreeSurface( loadedS );
			Uint32 colorkey = SDL_MapRGB( optimizedS->format, 0, 0xFF, 0xFF );
			SDL_SetColorKey(optimizedS, SDL_SRCCOLORKEY, colorkey);
			Surface_ptr img(optimizedS);
			m_sList[position] = img;
		}
		else
		{
			Surface_ptr img(loadedS);
			m_sList[position] = img;
		}
		return true;
	}
	else
	{
		cout<<"Error IMG: "<<IMG_GetError()<<endl;
		return false;
	}
}

Surface_ptr GameCache::GetSurface(const int index)
{
	return m_sList[index];
}

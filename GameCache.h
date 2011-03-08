#pragma once
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <boost\shared_ptr.hpp>
#include <string>

using namespace std;

typedef shared_ptr< SDL_Surface > Surface_ptr;

typedef map< int, Surface_ptr > SurfaceList;

/* Enumeratore utile per gestire le posizioni all'interno della lista */
enum loaded_image_index{
	PPLAYER,
	TERRAIN_TILE,
	PSPIKE_UP,
	PSPIKE_DOWN,
	PSPIKE_LEFT,
	PSPIKE_RIGHT
};

class GameCache
{
public:
	GameCache(void);
	~GameCache(void);

	void Init(void);

	Surface_ptr GetSurface(const int index);

private:
	/* Trattiamo un singleton, non è possibile chiamarne il costruttore */
	GameCache(const GameCache&);
	GameCache& operator=(const GameCache&);

	bool loadOptimized(string path, int position);

	SurfaceList m_sList;
};
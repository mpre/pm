#pragma once
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <boost\shared_ptr.hpp>
#include <string>

using namespace std;

typedef map< int, SDL_Surface* > SurfaceList;

/* Enumeratore utile per gestire le posizioni all'interno della lista */
enum loaded_image_index{
	PPLAYER,
	PPLAYER2,
	TERRAIN_TILE,
	PSPIKE_UP,
	PSPIKE_DOWN,
	PSPIKE_LEFT,
	PSPIKE_RIGHT,
	SPIKEBUTTON,
	FLARETOWER,
	FLARES
};

class GameCache
{
public:
	GameCache(void);
	virtual ~GameCache(void);

	void Init(void);

	SDL_Surface* GetSurface(const int index);

private:
	/* Trattiamo un singleton, non è possibile chiamarne il costruttore */
	GameCache(const GameCache&);
	GameCache& operator=(const GameCache&);

	bool loadOptimized(string path, int position);

	SurfaceList m_sList;
};
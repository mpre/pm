#pragma once

#include "../GameCache.h"
#include <Box2D\Box2D.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Surface* screen;
extern b2World* bWorld;
extern const short int BLOCK_DIM;

// Fattore di conversione metri->pixel
extern const float convF;

extern GameCache* GCache;

enum imgDirections{
		IRIGHT, 
		ILEFT,
		IUP,
		IDOWN
};

class CProcess
{
public:	
	CProcess(void);
	~CProcess(void);

	virtual void Update(void);
	virtual void SetSurface(const int surface_index)=0;
	virtual void Die(void)=0;
	virtual bool Hurt(void){ return false; };
	virtual void Touched(void) { };
	bool IsDead(void){ return m_bDead; };
	void SetDead(bool dead){ m_bDead = dead; };

protected:
	bool m_bDead;
};


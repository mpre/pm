#include "EventManager.h"


EventManager::EventManager(void)
{
}


EventManager::~EventManager(void)
{
}


void EventManager::ManageEvent(void)
{
	SDL_Event ev;
	while(SDL_PollEvent(&ev))
	{
		switch(ev.type)
		{
		case SDL_KEYDOWN:
			m_bPressed[ev.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			m_bPressed[ev.key.keysym.sym] = false;
			break;
		case SDL_QUIT:
			run = false;
			break;
		}
	}

	if( m_bPressed[PLAYER1_UP] )
		players[0]->AddForceToBody(b2Vec2(0,-15));
	if( m_bPressed[PLAYER1_DOWN] )
		players[0]->AddForceToBody(b2Vec2(0,5));
	if( m_bPressed[PLAYER1_LEFT] )
		players[0]->AddForceToBody(b2Vec2(-5,0));
	if( m_bPressed[PLAYER1_RIGHT] )
		players[0]->AddForceToBody(b2Vec2(5,0));
}
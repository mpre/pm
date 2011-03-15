#include "EventManager.h"

extern bool run;

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
			{
				switch(ev.key.keysym.sym)
				{
				case PLAYER1_UP:
					if( !m_bPressed[PLAYER1_UP] )
						players[0]->AddForceToBody(b2Vec2(0,-350));
					break;

				case PLAYER1_DOWN:
					if( !m_bPressed[PLAYER1_DOWN] )
						players[0]->AddForceToBody(b2Vec2(0,30));
					break;
				
				case PLAYER2_UP:
					if( !m_bPressed[PLAYER1_UP] )
						players[1]->AddForceToBody(b2Vec2(0,-350));
					break;

				case PLAYER2_DOWN:
					if( !m_bPressed[PLAYER1_DOWN] )
						players[1]->AddForceToBody(b2Vec2(0,30));
					break;

				default:
					break;
				}
				m_bPressed[ev.key.keysym.sym] = true;
				break;
			}
		case SDL_KEYUP:
			m_bPressed[ev.key.keysym.sym] = false;
			break;
		case SDL_QUIT:
			run = false;
			break;
		}
	}	

	/* Controllo tutte le direzioni, in questo modo se vengono schicciati
		sia sx che dx il giocatore ha un vettore di movimento orizzontale 
		pari a 0 aggiungendo due forze pari e contrarie*/
	if( m_bPressed[PLAYER1_LEFT] )
		players[0]->AddForceToBody(b2Vec2(-30,0));
	if( m_bPressed[PLAYER1_RIGHT] )
		players[0]->AddForceToBody(b2Vec2(30,0));
	if( m_bPressed[PLAYER2_LEFT] )
		players[1]->AddForceToBody(b2Vec2(-30,0));
	if( m_bPressed[PLAYER2_RIGHT] )
		players[1]->AddForceToBody(b2Vec2(30,0));

	if( m_bPressed[SDLK_ESCAPE] )
		run = false;
}
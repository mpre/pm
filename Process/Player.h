#pragma once
#include "CProcess.h"
#include <SDL.h>
#include <SDL_image.h>
#include <Box2D\Box2D.h>
#include <string>
#include <iostream>

using namespace std;

class State;

class Player :
	public CProcess
{
	friend class StandingState;
	friend class RunningState;
	friend class JumpingState;

public:
	Player( float, float );
	~Player(void);

	void SetSurface(const int surface_index);
	void SetBody( b2BodyDef &bodyDef );

	void Update( void );

	void AddForceToBody(b2Vec2& force);

	void SwitchState(State*);

protected:
	Player(void);
	b2Body* m_bBody;
	Surface_ptr m_sImg;
	State* m_sState;
	/* Ultimo millisecondo in cui è cambiata l'immagine */
	unsigned int m_tLast_surface_change;
	short int temp_i;
};


class State
{
public:
	State(Player*);
	~State(void) { m_pPlayer = 0; } ;

	virtual void Update()=0;
	virtual void AddForceToBody(b2Vec2& force)=0;

protected:
	static const int MAX_SPEED = 15;
	Player* m_pPlayer;

};

class StandingState :
	public State
{
public:
	StandingState(Player*);
	~StandingState(void) {};

	void Update();
	void AddForceToBody(b2Vec2& force);

private:
	// Direzione destra?
	bool m_bRight;
};

class RunningState :
	public State
{
public:
	RunningState(Player*);
	~RunningState(void) {};

	void Update();
	void AddForceToBody(b2Vec2& force);
private:
	bool firstRun;
};

class JumpingState:
	public State
{
public:
	JumpingState(Player*);
	~JumpingState(void) {};

	void Update();
	void AddForceToBody(b2Vec2& force);
};


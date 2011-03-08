/* MEMORY LEAK LIB */
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SDL.h"
#include <SDL_image.h>
#include "Process/CProcess.h"
#include "Process/Player.h"
#include "Process/Block.h"
#include "Process/ProcessManager.h"
#include "GameCache.h"
#include "EventManager.h"
#include <Box2D\Box2D.h>
#include <iostream>
#include <vector>

using namespace std;

// Funzioni di inizializzazione
bool InitEnv( void );
void EndEnv( void );
bool InitProcess( void );
void InitLevel( void );
void RunProcess( void );
void EndProcess( void );

// Variabili globali
const int SCREEN_WIDTH = 1272;
const int SCREEN_HEIGHT = 792;
const int SCREEN_BPP = 32;

const short int BLOCK_DIM = 24; // Dimensione di ogni blocco in pixel

const float convF = 48; // Fattore di conversione metri->pixel

SDL_Surface* screen = NULL;
b2World* bWorld = NULL;
GameCache* GCache = NULL;
ProcessManager* PMan = NULL;
EventManager* EvMan = NULL;

std::vector<Player*> players;

bool run = true;

int main( int argc, char* args[] )
{
	if(!InitEnv())
		return 0;
	
	if(InitProcess())
	{
		RunProcess();
	}
    
	EndProcess();	
	
	EndEnv();
	_CrtDumpMemoryLeaks();
    return true;    
}

bool InitEnv( void )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
		return false;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if( screen == NULL )
		return false;

	IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG|IMG_INIT_TIF);

	PMan = new ProcessManager();
	GCache = new GameCache();
	GCache->Init();

	EvMan = new EventManager();

	b2Vec2 gravity(0.0f, 120.0f);
	bWorld = new b2World(gravity, true);

	InitLevel();
	

	Player*	x = new Player(8.0f, 12.0f);
	x->SetSurface(PPLAYER);

	players.push_back(x);

	shared_ptr<Player> sp(x);

	

	PMan->Attach(sp);

	

	return true;
}

void EndEnv( void )
{
	b2Body* node = bWorld->GetBodyList();
	while(node)
	{
		bWorld->DestroyBody(node);
		node = bWorld->GetBodyList();
	}
	
	delete EvMan;

	delete PMan;
	//delete GCache;

	delete bWorld;
	SDL_FreeSurface(screen);
	IMG_Quit();
	SDL_Quit();
}

bool InitProcess( void )
{
	return true;
}

void RunProcess( void )
{
	ProcessManager* x124=PMan;

	SDL_Surface* background = SDL_LoadBMP("img/background.bmp");
	while(run)
	{
		EvMan->ManageEvent();

		SDL_BlitSurface(background, NULL, screen, NULL);
		bWorld->Step(1.0f / 60.0f, 15, 14);
		PMan->Update();
		SDL_Delay(5);
		SDL_Flip(screen);
	}
}

void EndProcess( void )
{
}

void InitLevel( void )
{
	std::list<Block> block_list;

	// Creo il bordo della finestra
	for (float i=0; i<=SCREEN_WIDTH; i+=BLOCK_DIM)
	{
		Block* b = new Block(i, SCREEN_HEIGHT-BLOCK_DIM-1);
		b->SetSurface(TERRAIN_TILE);
		shared_ptr<Block> sb(b);
		PMan->Attach(sb);
		block_list.push_back(*b);
		//boundary.Set(&b->GetBody()->GetFixtureList()->GetAABB().upperBound);
	}

	b2BodyDef bd;
	b2Body* ground = bWorld->CreateBody(&bd);
	b2EdgeShape shape;

	std::list<Block>::iterator i = block_list.begin();
	std::list<Block>::iterator end = block_list.end();
	b2Vec2 *v1=NULL,
		*v2=NULL,
		*v0=NULL,
		*v3=NULL;

	while(i!=end)
	{
		v0 = v1;
		v1 = v2;
		v2 = v3;
		v3 = new b2Vec2(i->GetBody()->GetFixtureList()->GetAABB(0).lowerBound);

		if(v1 && v2)
		{
			shape.Set(*v1, *v2);
			if(v0)
			{
				shape.m_hasVertex0 = true;
				shape.m_vertex0 = *v0;
			}
			if(v3)
			{
				shape.m_hasVertex3 = true;
				shape.m_vertex3 = *v3;
			}
			ground->CreateFixture(&shape, 0.0f);
		}

		++i;
	}
}
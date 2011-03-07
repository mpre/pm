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
void RunProcess( void );
void EndProcess( void );

// Variabili globali
const int SCREEN_WIDTH = 1272;
const int SCREEN_HEIGHT = 792;
const int SCREEN_BPP = 32;

const short int BLOCK_DIM = 24; // Dimensione di ogni blocco in pixel

const float convF = 50; // Fattore di conversione metri->pixel

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

	b2Vec2 gravity(0.0f, 25.0f);
	bWorld = new b2World(gravity, true);


	// Creo il bordo della finestra
	for (float i=0; i<=SCREEN_WIDTH; i+=BLOCK_DIM-1)
	{
		Block* b = new Block(i, SCREEN_HEIGHT-BLOCK_DIM);
		b->SetSurface(TERRAIN_TILE);
		shared_ptr<Block> sb(b);
		PMan->Attach(sb);
		b = new Block(i, 0);
		b->SetSurface(TERRAIN_TILE);
		shared_ptr<Block> sb2(b);
		PMan->Attach(sb2);
	}
	for (float i=BLOCK_DIM-1; i<=SCREEN_HEIGHT - BLOCK_DIM; i+=BLOCK_DIM-1)
	{
		Block* b = new Block(0,i);
		b->SetSurface(TERRAIN_TILE);
		shared_ptr<Block> sb(b);
		PMan->Attach(sb);
		b = new Block(SCREEN_WIDTH - BLOCK_DIM, i);
		b->SetSurface(TERRAIN_TILE);
		shared_ptr<Block> sb2(b);
		PMan->Attach(sb2);
	}



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
	SDL_Surface* background = SDL_LoadBMP("img/background.bmp");
	while(run)
	{
		EvMan->ManageEvent();

		SDL_BlitSurface(background, NULL, screen, NULL);
		bWorld->Step(1.0f / 60.0f, 10, 8);
		PMan->Update();
		SDL_Delay(20);
		SDL_Flip(screen);
	}
}

void EndProcess( void )
{
}
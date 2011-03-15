#pragma once

#include <SDL.h>
#include <map>
#include <vector>
#include "Process\Player.h"
#include "KEYSETTINGS.h"
#include <Box2D\Box2D.h>

extern std::vector<Player*> players;
extern bool run;

class EventManager
{
public:
	EventManager(void);
	~EventManager(void);

	void ManageEvent(void);

private:
	map<int, bool> m_bPressed; 
};


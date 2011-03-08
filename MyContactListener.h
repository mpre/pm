#pragma once
#include <Box2D\Box2D.h>
#include "Process\CProcess.h"

class MyContactListener :
	public b2ContactListener
{
public:
	MyContactListener(void);
	~MyContactListener(void);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact){};
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold){};
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){};
};


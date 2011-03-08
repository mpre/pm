#pragma once
#include "CProcess.h"
#include <Box2D\Box2D.h>

class Block :
	public CProcess
{
public:
	Block(float, float);
	~Block(void);

	void Update(void);

	void SetSurface(const int surface_index);
	void SetBody( b2BodyDef &bodyDef );
	void Die(void) {};

	b2Body* GetBody(void);

private:
	Block(void);
	b2Body* m_bBody;
	Surface_ptr m_sImg;
};


#pragma once
#include "CProcess.h"

enum spikeDirections{
		SPIKE_RIGHT, 
		SPIKE_LEFT,
		SPIKE_UP,
		SPIKE_DOWN
};

class Spike :
	public CProcess
{
public:
	Spike(float xPosition, float yPosition, 
		int direction);
	~Spike(void);

	void SetBody(b2BodyDef &bodydef);

	b2Body* GetBody(void);

	void Update(void);

	void SetSurface(const int surface_index){};

	void Die(void){};

	bool Hurt( void ){ return true; };

private:
	Spike(void);
	b2Body* m_bBody;
	Surface_ptr m_sImg;
	short int m_iDir;
};


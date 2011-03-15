#pragma once
#include "CProcess.h"
#include "Spike.h"
#include "ProcessManager.h"
#include <boost/shared_ptr.hpp>

extern ProcessManager* PMan;

class SpikeButton :
	public CProcess
{
public:
	SpikeButton(b2Vec2 &position, b2Vec2 &spikePosition, 
		int direction);
	~SpikeButton(void);

	void Die(void);
	void Update(void);
	void SetSurface(const int surface_index){};
	void Touched(void);

private:
	void SetBody(b2BodyDef &def);
	SpikeButton(void);

	b2Body* m_bBody;
	Uint32 _activationTime;
	b2Vec2 _spikePos;
	int _spikeDirection;
	Spike* _spike;
	Surface_ptr m_sImg;

	bool _activateSpike;
};


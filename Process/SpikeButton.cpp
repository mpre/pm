#include "SpikeButton.h"


SpikeButton::SpikeButton(b2Vec2 &position, b2Vec2 &spikePosition, 
	int direction)
{
	_spikePos = b2Vec2(spikePosition);
	_spikeDirection = direction;
	b2BodyDef def;
	def.position.Set(position.x/convF, position.y/convF);
	SetBody(def);

	m_sImg = GCache->GetSurface(SPIKEBUTTON);

	_activateSpike = false;
	_spike = NULL;
}


SpikeButton::SpikeButton(void)
{
}


SpikeButton::~SpikeButton(void)
{
	m_bBody = 0;
	_spike = 0;
}


void SpikeButton::Die(void)
{
}


void SpikeButton::Touched(void)
{
	_activateSpike = true;
}


void SpikeButton::SetBody(b2BodyDef &def)
{
	def.awake = false;
	def.fixedRotation = false;
	def.type = b2_staticBody;

	m_bBody = bWorld->CreateBody(&def);
	b2FixtureDef fixtDef;
	b2PolygonShape box;
	box.SetAsBox( ((float)(BLOCK_DIM))/(2.0f*convF), ((float)(BLOCK_DIM))/(2.0f*convF));
	fixtDef.shape = &box;
	fixtDef.restitution = 0.8f;
	fixtDef.friction = 0.7f;
	fixtDef.density = 10;

	fixtDef.filter.categoryBits = 0x0004;
	fixtDef.filter.maskBits = 0x0002;

	m_bBody->CreateFixture( &fixtDef );
	m_bBody->SetUserData(this);
}


void SpikeButton::Update(void)
{
	Uint32 now = SDL_GetTicks();
	if(_activateSpike)
	{
		if(_spike == NULL)
		{
			_spike = new Spike((float)_spikePos.x, (float)_spikePos.y, 
				_spikeDirection);
			shared_ptr<Spike> ss(_spike);
			PMan->Attach(ss);
			_activationTime = now;
		}
		_activateSpike = false;
	}

	if (now > _activationTime + 3500 && _spike != NULL)
	{
		_spike->SetDead(true);
		_spike = NULL;
	}
	SDL_Rect pos;
	pos.x = m_bBody->GetPosition().x * convF;
	pos.y = m_bBody->GetPosition().y * convF;

	SDL_BlitSurface(m_sImg.get(), NULL, screen, &pos);
}

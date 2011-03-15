#include "Block.h"


Block::Block(float xPosition=0.0f, float yPosition=0.0f) : CProcess()
{
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set( xPosition/convF, yPosition/convF );
	def.awake = false;
	SetBody(def);
}


Block::~Block(void)
{
	m_bBody = NULL;
}


void Block::SetBody( b2BodyDef &bodyDef )
{
	bodyDef.fixedRotation = true;
	m_bBody = bWorld->CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	b2PolygonShape box;
	box.SetAsBox( ((float)(BLOCK_DIM))/(2.0f*convF), ((float)(BLOCK_DIM))/(2.0f*convF));
	fixDef.shape = &box;
	fixDef.restitution = 0.0f;
	fixDef.friction = 0.7f;
	fixDef.density = 10;
	// Problema mappe tiled. Questo valore viene filtrato da player
	fixDef.filter.categoryBits = 0x0004;
	fixDef.filter.maskBits = 0x0002;

	m_bBody->CreateFixture( &fixDef );
	m_bBody->SetUserData(this);
}

b2Body* Block::GetBody(void)
{
	return m_bBody;
}

void Block::Update(void)
{
	SDL_Rect pos;
	pos.x = m_bBody->GetPosition().x * convF;
	pos.y = m_bBody->GetPosition().y * convF;

	SDL_Rect clip;
	clip.w = BLOCK_DIM;
	clip.h = BLOCK_DIM;

	clip.x = 0;
	clip.y = 0;

	SDL_BlitSurface(m_sImg, &clip, screen, &pos);
}


void Block::SetSurface(const int surface_index)
{
	m_sImg = GCache->GetSurface( surface_index );
}
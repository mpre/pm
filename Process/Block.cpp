#include "Block.h"


Block::Block(float xPosition=0.0f, float yPosition=0.0f) : CProcess()
{
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set( xPosition/convF, yPosition/convF );
	def.awake = true;
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
	fixDef.restitution = 0.1f;
	fixDef.friction = 0.6f;
	fixDef.density = 1;
	m_bBody->CreateFixture( &fixDef );
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

	SDL_BlitSurface(m_sImg.get(), &clip, screen, &pos);
}


void Block::SetSurface(const int surface_index)
{
	m_sImg = GCache->GetSurface( surface_index );
}
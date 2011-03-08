#include "Spike.h"

Spike::Spike(float xPosition, float yPosition, 
	int direction) : CProcess()
{
	m_iDir = direction;
	b2BodyDef def;
	def.type = b2_staticBody;
	def.position.Set( xPosition/convF, yPosition/convF );
	def.awake = false;
	SetBody(def);
}


Spike::Spike(void)
{
	
}


Spike::~Spike(void)
{
	m_bBody = NULL;
}


void Spike::SetBody(b2BodyDef &bodyDef)
{
	bodyDef.fixedRotation = true;
	m_bBody = bWorld->CreateBody(&bodyDef);
	b2FixtureDef fixDef;

	b2PolygonShape triangle;
	b2Vec2 v1,v2,v3;
	switch(m_iDir){
		case SPIKE_UP:
			v1 = b2Vec2(0,-BLOCK_DIM/(2.0f * convF)); 
			v2 = b2Vec2(BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(-BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF));
			m_sImg = GCache->GetSurface(PSPIKE_UP);
			break;
		case SPIKE_DOWN:
			v1 = b2Vec2(BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF)); 
			v2 = b2Vec2(BLOCK_DIM/(2.0f * convF), -BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(0,BLOCK_DIM/(2.0f * convF));
			m_sImg = GCache->GetSurface(PSPIKE_DOWN);
			break;
		case SPIKE_RIGHT:
			v1 = b2Vec2(-BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF)); 
			v2 = b2Vec2(-BLOCK_DIM/(2.0f * convF),-BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(BLOCK_DIM/(2.0f * convF), 0);
			m_sImg = GCache->GetSurface(PSPIKE_RIGHT);
			break;
		case SPIKE_LEFT:
			v1 = b2Vec2(-BLOCK_DIM/(2.0f * convF),0); 
			v2 = b2Vec2(BLOCK_DIM/(2.0f * convF), -BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(BLOCK_DIM/(2.0f * convF), BLOCK_DIM/(2.0f * convF));
			m_sImg = GCache->GetSurface(PSPIKE_LEFT);
			break;
	}
	b2Vec2 v[3] = {v1,v2,v3};
	triangle.Set(v, 3);

	/*b2PolygonShape triangle;
	triangle.SetAsBox( ((float)(BLOCK_DIM))/(2.0f*convF), ((float)(BLOCK_DIM))/(2.0f*convF));
	switch(m_iDir){
		case SPIKE_UP:
			m_sImg = GCache->GetSurface(PSPIKE_UP);
			break;
		case SPIKE_DOWN:
			m_sImg = GCache->GetSurface(PSPIKE_DOWN);
			break;
		case SPIKE_RIGHT:
			m_sImg = GCache->GetSurface(PSPIKE_RIGHT);
			break;
		case SPIKE_LEFT:
			m_sImg = GCache->GetSurface(PSPIKE_LEFT);
			break;
	}*/
	fixDef.shape = &triangle;
	fixDef.restitution = 0.0f;
	fixDef.friction = 1.0f;
	fixDef.density = 0.0f;

	fixDef.filter.maskBits = 0x0002; // Collide solo con i giocatori
	fixDef.filter.categoryBits = 0x0016;

	m_bBody->CreateFixture(&fixDef);
	m_bBody->SetUserData(this);

}

b2Body* Spike::GetBody(void)
{
	return m_bBody;
}

void Spike::Update(void)
{
	SDL_Rect pos;
	pos.x = m_bBody->GetPosition().x * convF;
	pos.y = m_bBody->GetPosition().y * convF;

	SDL_BlitSurface(m_sImg.get(), NULL, screen, &pos);
}
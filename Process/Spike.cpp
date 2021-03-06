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
	m_bBody->SetUserData(this);
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

	b2PolygonShape triangle;
	b2Vec2 v1,v2,v3;
	switch(m_iDir){
		case IUP:
			v1 = b2Vec2(0,-BLOCK_DIM/(2.0f * convF)); 
			v2 = b2Vec2(BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(-BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF));
			m_sImg = GCache->GetSurface(PSPIKE_UP);
			break;
		case IDOWN:
			v1 = b2Vec2(BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF)); 
			v2 = b2Vec2(BLOCK_DIM/(2.0f * convF), -BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(0,BLOCK_DIM/(2.0f * convF));
			m_sImg = GCache->GetSurface(PSPIKE_DOWN);
			break;
		case IRIGHT:
			v1 = b2Vec2(-BLOCK_DIM/(2.0f * convF),BLOCK_DIM/(2.0f * convF)); 
			v2 = b2Vec2(-BLOCK_DIM/(2.0f * convF),-BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(BLOCK_DIM/(2.0f * convF), 0);
			m_sImg = GCache->GetSurface(PSPIKE_RIGHT);
			break;
		case ILEFT:
			v1 = b2Vec2(-BLOCK_DIM/(2.0f * convF),0); 
			v2 = b2Vec2(BLOCK_DIM/(2.0f * convF), -BLOCK_DIM/(2.0f * convF));
			v3 = b2Vec2(BLOCK_DIM/(2.0f * convF), BLOCK_DIM/(2.0f * convF));
			m_sImg = GCache->GetSurface(PSPIKE_LEFT);
			break;
	}
	b2Vec2 v[3] = {v1,v2,v3};
	triangle.Set(v, 3);

	b2FixtureDef fixDef;
	fixDef.shape = &triangle;
	fixDef.restitution = 0.0f;
	fixDef.friction = 1.0f;
	fixDef.density = 0.0f;

	fixDef.filter.maskBits = 0x0002; // Collide solo con i giocatori
	fixDef.filter.categoryBits = 0x0016;

	m_bBody->CreateFixture(&fixDef);
	
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

	SDL_BlitSurface(m_sImg, NULL, screen, &pos);
}
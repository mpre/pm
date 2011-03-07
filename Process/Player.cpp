#include "Player.h"


Player::Player(float xPosition=0.0f, float yPosition=0.0f) : CProcess(), temp_i(0)
{
	m_tLast_surface_change = SDL_GetTicks();
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position.Set( xPosition, yPosition );
	def.awake = true;
	SetBody(def);
	m_sState = new StandingState(this);
}


Player::~Player(void)
{
	bWorld->DestroyBody(m_bBody);
}


void Player::SetSurface(const int surface_index)
{
	m_sImg = GCache->GetSurface( surface_index );
}


void Player::SetBody( b2BodyDef &bodyDef )
{
	bodyDef.fixedRotation = true;
	m_bBody = bWorld->CreateBody(&bodyDef);
	b2FixtureDef fixDef;
	b2PolygonShape box;
	box.SetAsBox( ((float)(BLOCK_DIM))/(2.0f*convF), ((float)(BLOCK_DIM))/(2.0f*convF) );
	fixDef.shape = &box;
	fixDef.restitution = 0.0f;
	fixDef.density = 1;
	m_bBody->CreateFixture( &fixDef );
}


void Player::Update( void )
{
	m_sState->Update();
}


void Player::AddForceToBody(b2Vec2& force)
{
	m_sState->AddForceToBody(force);
}

void Player::SwitchState(State* s)
{
	delete m_sState;
	m_sState = s;
}

/* State */
State::State(Player* p)
{
	m_pPlayer = p;
}


/* Standing state*/
StandingState::StandingState(Player* p) : State(p)
{
	m_bRight = (m_pPlayer->m_bBody->GetLinearVelocity().x >= 0);
	m_pPlayer->temp_i = (m_bRight) ? 3 : 0;
}

void StandingState::Update()
{
	unsigned int now = SDL_GetTicks();
	if (now > m_pPlayer->m_tLast_surface_change + 250)
	{
		m_pPlayer->m_tLast_surface_change = now;
		m_pPlayer->temp_i += 1;
		m_pPlayer->temp_i = m_pPlayer->temp_i % 3;
		if (m_bRight)
			m_pPlayer->temp_i += 3;
	}

	SDL_Rect pos;
	pos.x = m_pPlayer->m_bBody->GetPosition().x * convF;
	pos.y = m_pPlayer->m_bBody->GetPosition().y * convF;
	
	SDL_Rect clip;
	clip.w = BLOCK_DIM;
	clip.h = BLOCK_DIM;

	clip.x = BLOCK_DIM * m_pPlayer->temp_i;
	clip.y = BLOCK_DIM;

	SDL_BlitSurface(m_pPlayer->m_sImg.get(), &clip, screen, &pos);
}

void StandingState::AddForceToBody(b2Vec2& force)
{
	m_pPlayer->m_bBody->ApplyForce(force, 
		m_pPlayer->m_bBody->GetWorldCenter());
	if( abs(force.y) > 0.1 )
		m_pPlayer->SwitchState(new JumpingState(m_pPlayer));
	else 
		m_pPlayer->SwitchState(new RunningState(m_pPlayer));
}

/* Running state*/

const int MAX_VELOCITY = 15;

RunningState::RunningState(Player* p) : State(p)
{
	m_pPlayer->temp_i = 0;
	firstRun = true;
}

void RunningState::Update()
{
	if(firstRun)
		firstRun = false;
	unsigned int now = SDL_GetTicks();
	if (now > m_pPlayer->m_tLast_surface_change + 100)
	{
		m_pPlayer->m_tLast_surface_change = now;
		++(m_pPlayer->temp_i);
		m_pPlayer->temp_i = m_pPlayer->temp_i % 3 + 
			(m_pPlayer->m_bBody->GetLinearVelocity().x > 0) * 3;
	}
	
	SDL_Rect pos;
	pos.x = m_pPlayer->m_bBody->GetPosition().x * convF;
	pos.y = m_pPlayer->m_bBody->GetPosition().y * convF;
	
	SDL_Rect clip;
	clip.w = BLOCK_DIM;
	clip.h = BLOCK_DIM;

	clip.x = BLOCK_DIM * m_pPlayer->temp_i;
	clip.y = 0;

	SDL_BlitSurface(m_pPlayer->m_sImg.get(), &clip, screen, &pos);

	if(abs(m_pPlayer->m_bBody->GetLinearVelocity().x) == 0.0f)
	{
		m_pPlayer->SwitchState(new StandingState(m_pPlayer));
	}	
}

void RunningState::AddForceToBody(b2Vec2& force)
{
	if( abs(force.y) >= 0.1 )
	{
		m_pPlayer->m_bBody->ApplyForce(force, m_pPlayer->m_bBody->GetWorldCenter());
		m_pPlayer->SwitchState(new JumpingState(m_pPlayer));
	}
	else
	{
		if(abs(m_pPlayer->m_bBody->GetLinearVelocity().x) > MAX_VELOCITY)
		{
			force.x = 0;
			m_pPlayer->m_bBody->ApplyForce(force, m_pPlayer->m_bBody->GetWorldCenter());
			if(m_pPlayer->m_bBody->GetLinearVelocity().x > 0)
				m_pPlayer->m_bBody->SetLinearVelocity(
					b2Vec2 (MAX_VELOCITY,m_pPlayer->m_bBody->GetLinearVelocity().y));
			else
				m_pPlayer->m_bBody->SetLinearVelocity(
					b2Vec2 (-MAX_VELOCITY,m_pPlayer->m_bBody->GetLinearVelocity().y));
		}
		else
			m_pPlayer->m_bBody->ApplyForce(force, m_pPlayer->m_bBody->GetWorldCenter());
	}
}

/* Jumping state*/
JumpingState::JumpingState(Player* p) : State(p)
{
	 m_pPlayer->temp_i = (m_pPlayer->m_bBody->GetLinearVelocity().x >= 0) ? 3 : 0;
}

void JumpingState::Update()
{
	unsigned int now = SDL_GetTicks();
	if (now > m_pPlayer->m_tLast_surface_change + 500)
	{
		m_pPlayer->m_tLast_surface_change = now;
		m_pPlayer->temp_i += 1;
		m_pPlayer->temp_i = m_pPlayer->temp_i % 3;
		if (m_pPlayer->m_bBody->GetLinearVelocity().x >= 0)
			m_pPlayer->temp_i += 3;
	}

	SDL_Rect pos;
	pos.x = m_pPlayer->m_bBody->GetPosition().x * convF;
	pos.y = m_pPlayer->m_bBody->GetPosition().y * convF;
	
	SDL_Rect clip;
	clip.w = BLOCK_DIM;
	clip.h = BLOCK_DIM;

	clip.x = BLOCK_DIM * m_pPlayer->temp_i;
	clip.y = BLOCK_DIM;

	SDL_BlitSurface(m_pPlayer->m_sImg.get(), &clip, screen, &pos);

	bool standing = false;
	for(b2ContactEdge* contatto = m_pPlayer->m_bBody->GetContactList();
		contatto; contatto = contatto->next)
	{
		if(contatto->contact->GetManifold()->localNormal.y < 0 &&
			m_pPlayer->m_bBody->GetLinearVelocity().y == 0)
			standing = true;
	}

	if(standing)
	{
		m_pPlayer->SwitchState(new RunningState(m_pPlayer));
	}
}

void JumpingState::AddForceToBody(b2Vec2& force)
{
	force.y = 0;
	if(abs(m_pPlayer->m_bBody->GetLinearVelocity().x) > MAX_VELOCITY)
		force.x = 0;
	m_pPlayer->m_bBody->ApplyForce(force, m_pPlayer->m_bBody->GetWorldCenter());
}
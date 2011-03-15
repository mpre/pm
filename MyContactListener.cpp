#include "MyContactListener.h"


MyContactListener::MyContactListener(void)
{
}


MyContactListener::~MyContactListener(void)
{
}


void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Body* b1 = contact->GetFixtureA()->GetBody();
	b2Body* b2 = contact->GetFixtureB()->GetBody();

	if(b1->GetUserData())
		if(b2->GetUserData())
			if(((CProcess*)b2->GetUserData())->Hurt())
				((CProcess*)b1->GetUserData())->Die();
			else
				((CProcess*)b1->GetUserData())->Touched();
	if(b2->GetUserData())
		if(b1->GetUserData())
			if(((CProcess*)b1->GetUserData())->Hurt())
				((CProcess*)b2->GetUserData())->Die();
			else
				((CProcess*)b2->GetUserData())->Touched();

	
}
#include "ProcessManager.h"


ProcessManager::ProcessManager(void)
{
}


ProcessManager::~ProcessManager(void)
{
	m_pList.clear();
}


void ProcessManager::Attach(CProcess_ptr p)
{
	if(p!=NULL)
	{
		m_pList.push_back(p);
	}
}

void ProcessManager::Detach(CProcess_ptr)
{
	// TODO, per ora vedere dentro a metodo Update
}


void ProcessManager::Update(void)
{
	ProcessList::iterator i = m_pList.begin();
	ProcessList::iterator end = m_pList.end();

	while( i!=end )
	{
		shared_ptr<CProcess> p(*i);
		if(!p->IsDead())
		{
			p->Update();
			++i;
		}
		else
		{
			// Cancello il processo morto
			i = m_pList.erase(i);
		}
	}
}

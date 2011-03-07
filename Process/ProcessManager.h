#pragma once
#include <list>
#include "CProcess.h"
#include <boost\shared_ptr.hpp>

typedef shared_ptr<CProcess> CProcess_ptr;
typedef std::list< CProcess_ptr > ProcessList;

class ProcessManager
{
public:
	ProcessManager(void);
	~ProcessManager(void);

	void Attach(CProcess_ptr);
	void Detach(CProcess_ptr);

	void Update(void);

private:
	ProcessList m_pList;
};
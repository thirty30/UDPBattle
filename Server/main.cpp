#include "stdafx.h"

n32 main(n32 argc, tcchar** argv)
{
	CServer* pServer = new CServer();
	if (pServer->Init() == false)
	{
		return -1;
	}
	pServer->Run();
	pServer->Clear();
	return 0;
}

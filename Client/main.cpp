#include "stdafx.h"

n32 main(n32 argc, tcchar** argv)
{
	if (argc < 2)
	{
		return 0;
	}
	n32 nPort = TA2N32(argv[1]);

	CGame* pGame = new CGame();
	pGame->SetUDPPort(nPort);
	if (pGame->InitGame() == false)
	{
		return 0;
	}
	pGame->LoopGame();
	delete pGame;
	return 0;
}



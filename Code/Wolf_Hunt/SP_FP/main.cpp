#include "GameManager.h"

int main(int argc, char ** args)
{
	GameManager * gm = new GameManager();
	gm->Init();
	gm->MainLoop();
	delete gm;
	return 0;
}
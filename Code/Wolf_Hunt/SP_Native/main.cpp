#include "GameManager.h"

int main(int argc, char ** args)
{
	SP_Native::GameManager * gm = new SP_Native::GameManager();
	gm->Init();
	gm->MainLoop();
	delete gm;
	return 0;
}
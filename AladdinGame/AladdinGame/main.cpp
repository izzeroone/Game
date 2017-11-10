#include <Windows.h>
#include <iostream>

#include "Game\AladdinGame.h"

using namespace std;
LINK_FRAMEWORK

#define APP_TITTLE L"Aladdin"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow)
{
	Game* myGame;
	myGame = new AladdinGame(hInstance, APP_TITTLE);

	myGame->init();
	myGame->run();
	myGame->release();

	delete myGame;
}

#ifndef __GAME_H__
#define __GAME_H__

#include <windows.h>


#include "../Framework/Singleton/windowGUI.h"
#include "../Framework/Singleton/dxdevice.h"
#include "../Framework/sprite.h"
#include "../Framework/Singleton/gametime.h"
#include "../Framework/Singleton/gamecontroller.h"

DEFINE_FRAMEWORK_START

//define basic game's loop
class Game
{
public:
	virtual ~Game(void);

	static int isExit;

	Game(HINSTANCE, LPWSTR = L"Window Game", int width = 800, int height = 600, int fps = 30, int isFullScreen = 0);
	void virtual init();						// init your objects
	void virtual release();						// release your objects

	void virtual updateInput(float deltatime);	// update input, include played objects and menu button
	void virtual update(float deltatime);		// update your objects
	void virtual draw();						// draw your objects
	void virtual loadResource();

	void run();
	void render();
	static void exit();			// exit the game. call: Game::exit()
	static WindowGUI* getWindow();
protected:
	pWindowGUI wnd_Instance;		// for init window. 
	pGameTime _gametime;
	pDXDevice _dxdevice;
	pGameController _input;
	LPD3DXSPRITE _spriteHandle;
	static WindowGUI *hWindow;
private:
	float _frameRate;			// time for 1 frame, milisecond
	float _oldTime;
	float _deltaTime;
};

typedef Game* pGame;

DEFINE_FRAMEWORK_END

#endif // !__GAME_H__


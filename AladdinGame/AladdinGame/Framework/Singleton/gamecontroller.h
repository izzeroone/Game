

#ifndef __GAME_CTRL_H__
#define __GAME_CTRL_H__

#include "../define.h"
#include "windowGUI.h"
#include "../../../sigcxx/include/sigcxx/sigcxx.hpp"

#include <vector>

DEFINE_FRAMEWORK_START

#define KEYBOARD_BUFFER_SIZE 1024

typedef LPDIRECTINPUT			pGInput;
typedef LPDIRECTINPUTDEVICE8	pGKeyboard;


[event_source(native)]
class GameController
{
public:
	~GameController();

	static GameController* getInstance();
	static void release();

	bool	init(HWND, HINSTANCE);			// should be called in game::init()
	void	update();						// should be called in main game loop
	int		isKeyDown(int keycode);			// check if keycode is down.
	bool	isKeyPressed(int keycode);
	bool	isKeyRelease(int keycode);

	sigcxx::SignalRef<const int> keyPressed();
	sigcxx::SignalRef<const int> keyReleased();


private:
	GameController();
	static GameController* _instance;
			
	pGInput		_input;
	pGKeyboard	_keyboard;
	BYTE		_keyBuffer[256];			// BYTE = unsigned char
	HWND		_hWnd;						// refference to another place. Dont release!!!
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];

	sigcxx::Signal<const int> _keyPressed;
	sigcxx::Signal<const int> _keyReleased;
	


	bool		_previousKeyBuffer[256];
};
typedef GameController *pGameController;

DEFINE_FRAMEWORK_END

#endif // !__INPUT_CTRL_H__

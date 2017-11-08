#include "GameController.h"

LINK_FRAMEWORK

GameController::GameController()
{
	_input = NULL;
	_keyboard = NULL;
	ZeroMemory(_keyBuffer, 256);
}

GameController::~GameController()
{
	if (_input != NULL)
		this->_input->Release();
	if (_keyboard != NULL)
		this->_keyboard->Release();
}


GameController* GameController::_instance = nullptr;

GameController* GameController::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new GameController();
	}
	return _instance;
}

void GameController::release()
{
	delete _instance;
	_instance = nullptr;
}

bool GameController::init(HWND hWnd, HINSTANCE hinstance)
{
	//_keydownQueue.clear();
	//_keyupQueue.clear();
	this->_hWnd = hWnd;
	HRESULT rs;
	rs = DirectInput8Create(
		hinstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&_input,
		NULL);
	if (rs != DI_OK)
		return false;

	rs = _input->CreateDevice(GUID_SysKeyboard, (LPDIRECTINPUTDEVICEW*)&_keyboard, NULL);
	if (rs != DI_OK)
		return false;

	rs = _keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (rs != DI_OK)
		return false;

	rs = _keyboard->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (rs != DI_OK)
		return false;

	// Set Property for keyboard buffer.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.diph.dwObj = 0;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE;

	rs = _keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (rs != DI_OK)
		return false;

	rs = _keyboard->Acquire();
	if (rs != DI_OK)
		return false;

	return true;
}

void GameController::update()
{
	for (int i = 0; i < 256; i++)
	{
		_previousKeyBuffer[i] = ((_keyBuffer[i] & 0x80) > 0);
	}

	// collect state of all of keys.
	_keyboard->GetDeviceState(sizeof(this->_keyBuffer), _keyBuffer);
	if (isKeyDown(DIK_ESCAPE))
	{
		PostMessage(_hWnd, WM_QUIT, 0, 0);
	}

	DWORD dw = KEYBOARD_BUFFER_SIZE;
	HRESULT rs = _keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvents, &dw, 0);

	int keycode, keystate;
	for (DWORD i = 0; i < dw; i++)		// not use for each statement.
	{
		keycode = _keyEvents[i].dwOfs;
		keystate = _keyEvents[i].dwData;
		if ((keystate & 0x80) > 0)
		{
			_keyPressed.Emit(keycode); // raise a key press signal
		}
		else
		{
			_keyReleased.Emit(keycode);
		}
	}
}

int GameController::isKeyDown(int keycode)
{
	return ((_keyBuffer[keycode] & 0x80) > 0);
}

bool GameController::isKeyPressed(int keycode)
{
	// Khôgn dùng được
	return isKeyDown(keycode) && !(_previousKeyBuffer[keycode]);
}

bool GameController::isKeyRelease(int keycode)
{
	// Không dùng được 
	return !isKeyDown(keycode) && (_previousKeyBuffer[keycode]);
}

sigcxx::SignalRef<const int> GameController::keyPressed()
{
	return _keyPressed;
}

sigcxx::SignalRef<const int> GameController::keyReleased()
{
	return _keyReleased;
}

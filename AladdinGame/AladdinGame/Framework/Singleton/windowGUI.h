#pragma once

//Lớp cửa sổ giao diện
#ifndef __WINDOWGUI_H__
#define __WINDOWGUI_H__

#include <Windows.h>
#include "../define.h"

DEFINE_FRAMEWORK_START

class WindowGUI
{
public:
	WindowGUI(HINSTANCE hInstance, LPWSTR name, int width, int height, int fps, int isFullScreen);
	~WindowGUI();
	void initWindow();

	int isFullScreen();
	int getWidth();
	int getHeight();
	int getFrameRate();
	HWND getWnd();
	HINSTANCE getInstance();
protected:

	HINSTANCE		_hInstance;
	HWND			_hWnd;

	LPWSTR			_wcName;
	int				_isFullScreen;

	int				_width;
	int				_height;
	int				_fps;

	static HRESULT CALLBACK winProc(HWND, UINT, WPARAM, LPARAM);
	WindowGUI();
private:

};

//Pointer to a Windows object
typedef WindowGUI* pWindowGUI;

DEFINE_FRAMEWORK_END

#endif // !__WindowGUI_H__

#include "dxdevice.h"
LINK_FRAMEWORK

DXDevice* DXDevice::_instance = nullptr;

DXDevice::DXDevice(void)
{
	_pD3d = NULL;
	_pDevice = NULL;
	_surface = NULL;
}

void DXDevice::Init(WindowGUI windows)
{
	_pD3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS	l_preParameter;

	ZeroMemory(&l_preParameter, sizeof(l_preParameter));

	l_preParameter.SwapEffect = D3DSWAPEFFECT_DISCARD;
	l_preParameter.Windowed = windows.isFullScreen() ? FALSE : TRUE;
	l_preParameter.hDeviceWindow = windows.getWnd();
	l_preParameter.BackBufferFormat = D3DFMT_A8R8G8B8;
	l_preParameter.BackBufferCount = 1;
	l_preParameter.BackBufferHeight = windows.getHeight();
	l_preParameter.BackBufferWidth = windows.getWidth();
	_pD3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		windows.getWnd(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&l_preParameter,
		&_pDevice);

	if (_pDevice == NULL)
		throw new exception("Can not create device");

	_pDevice->GetBackBuffer(NULL, NULL, D3DBACKBUFFER_TYPE_MONO, &_surface);
}

DXDevice* DXDevice::getInstance()
{
	if (_instance == NULL)
		_instance = new DXDevice();
	return _instance;
}

DXDevice::~DXDevice(void)
{
	if (_pD3d != NULL)
		_pD3d->Release();
	if (_pDevice != NULL)
		_pDevice->Release();
	if (_surface != NULL)
		_surface->Release();
}

void DXDevice::release()
{
	delete _instance;
	_instance = NULL;
}

void DXDevice::present()
{
	this->_pDevice->Present(0, 0, 0, 0);
}


void DXDevice::clearScreen()
{
	this->_pDevice->ColorFill(_surface, NULL, D3DCOLOR_XRGB(0, 0, 0));
}

LPDIRECT3DDEVICE9 DXDevice::getDevice()
{
	return _pDevice;
}

LPDIRECT3DSURFACE9 DXDevice::getSurface()
{
	return _surface;
}

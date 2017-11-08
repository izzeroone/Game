
#ifndef __DXDEVICE_MANAGER_H__
#define __DXDEVICE_MANAGER_H__
//Lớp Device của DirectX theo mẫu thiết kế Singeton
#include "../define.h"
#include "windowGUI.h"

DEFINE_FRAMEWORK_START

class DXDevice
{
public:

	~DXDevice(void);
	static DXDevice* getInstance();
	static void release();
	void clearScreen();
	void present();
	void Init(WindowGUI);

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSURFACE9 getSurface();

private:
	static DXDevice* _instance;
	LPDIRECT3D9			_pD3d;
	LPDIRECT3DDEVICE9	_pDevice;
	LPDIRECT3DSURFACE9	_surface;
	DXDevice(void);
};
typedef DXDevice *pDXDevice;
DEFINE_FRAMEWORK_END

#endif // !__DXDEVICE_MANAGER_H__

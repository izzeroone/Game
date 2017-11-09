#ifndef __GAME_FRAMEWORK__
#define __GAME_FRAMEWORK__

#define _USE_MATH_DEFINES

#include <d3d9.h>		// d3d9.lib
#include <d3dx9.h>		// d3dx9.lib
#include <dinput.h>		// dinput8.lib, dxguid.lib
#include <dsound.h>		// dsound.lib

#include <windows.h>
#include <exception>
#include <math.h>
#include <string>
#include <map>
#include <vector>


using namespace std;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 448
#define SCALE_FACTOR 2.0f

#define C_WHITE D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)				// màu trắng
#define COLOR_KEY D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f)				// màu khi mà load hình nó bỏ qua > trong suốt mau hong

enum eObjectID
{
	ALADDIN = 0, // main character
	LAND = 1,
	ROPE = 2,
	MAP1 = 3
};

enum eStatus
{

	NORMAL = 0,					// 00000 = 0	
	MOVING_LEFT = (1 << 0),				// 00001 = 2^0
	MOVING_RIGHT = (1 << 1),				// 00010 = 2^1
	JUMPING = (1 << 2),				// 00100 = 2^2
	LAYING_DOWN = (1 << 3),				// 01000 = 2^3
	RUNNING = (1 << 4),				// 10000 = 2^4
	LOOKING_UP = (1 << 5),				// 2^5
	THROWING = (1 << 6),

	// Trạng thái huỷ, lúc này, đối tượng không update, không draw, ở scene kiểm tra nếu phát hiện trạng thái này thì huỷ đối tượng.
	DESTROY = (1 << 7),

	// Trạng thái nổ, lúc này có thể vẽ các đám cháy, vụ nổ.
	BURST = (1 << 8),

	// Dùng cho aircraft, trạng thái thể hiện đang nổ để chuyển từ cái máy bay thành đồ tiếp đạn.
	EXPLORING = (1 << 9),

	// Dùng cho aircraft, trạng thái đồ tiếp đạn.
	EXPLORED = (1 << 10),

	DYING = (1 << 11),
	EXPOSING = (1 << 15),
	FALLING = (1 << 16),
	SWIMING = (1 << 18),
	DIVING = (1 << 19),
	HIDDEN = (1 << 20),
	WAITING = (1 << 31),

	//Dung cho aladdin nhay hieu ung
	MOVINGJUMPING = (1 << 12), 
	CLIMBVERTICAL = (1 << 14),
	CLIMBHORIZON = (1 << 21),
	MOVE_UP = (1 << 22),
	MOVE_DOWN = (1 << 23),
	BORING1 = (1 << 24),
	BORING2 = (1 << 25),
	BORING3 = (1 << 26)
};



enum eDirection
{
	NONE = 0,
	TOP = 1,
	BOTTOM = 2,
	LEFT = 4,
	RIGHT = 8,
	ALL = (TOP | BOTTOM | LEFT | RIGHT),
};

enum eRopeType
{
	VERTICAL = 0,
	HORIZONTAL = 1
};

enum eWeaponType
{
	SWORD,
	APPLE
};

enum eCommand
{
	MOVELEFT,
	MOVERIGHT,
	JUMP,
	CLIMB
};

enum eSoundId
{
	// Nhạc nền map 1
	BACKGROUND_STAGE1
};

typedef D3DXVECTOR3 GVector3;
typedef D3DXVECTOR2 GVector2;
#define VECTOR2ZERO GVector2(0.0f, 0.0f)
#define VECTOR2ONE  GVector2(1.0f, 1.0f)


#define DEFINE_FRAMEWORK_START		namespace Framework {

#define DEFINE_FRAMEWORK_END	}

#define LINK_FRAMEWORK		using namespace Framework;

#ifndef SAFE_DELETE

#define SAFE_DELETE(p) \
if(p) \
{\
	delete (p); \
	p = nullptr; \
} \

#endif // !SAFE_DELETE



#endif // !__GAME_FRAMEWORK__


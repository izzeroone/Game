#ifndef __ALADDIN_GAME_H__
#define __ALADDIN_GAME_H__

#include "Game.h"
#include "../Framework/GameObject.h"
class AladdinGame : public Game
{
public:
	AladdinGame(HINSTANCE hInstance, LPWSTR title);
	~AladdinGame();

	void init();						// init your objects
	void release();						// release your objects

	void updateInput(float deltatime);	// update input, include played objects and menu button
	void update(float deltatime);		// update your objects
	void draw();						// draw your objects
	void loadResource();

private:
	LPDIRECT3DSURFACE9 _Background;
	GameObject* _aladdin;
};

#endif // !__CONTRA_GAME_H__

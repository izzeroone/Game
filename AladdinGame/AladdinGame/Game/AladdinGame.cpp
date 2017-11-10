#include "AladdinGame.h"
#include "SceneManager.h"
#include "TestScene.h"
AladdinGame::AladdinGame(HINSTANCE hInstance, LPWSTR title) : Game(hInstance, title, WINDOW_WIDTH, WINDOW_HEIGHT)
{

}

AladdinGame::~AladdinGame()
{
}

void AladdinGame::init()
{
	Game::init();
	// init game
#if _DEBUG
	SceneManager::getInstance()->addScene(new TestScene());
#else
	SceneManager::getInstance()->addScene(new IntroScene());
#endif
}

void AladdinGame::release()
{
	Game::release();

	// release game
	SceneManager::getInstance()->clearScenes();
}

void AladdinGame::updateInput(float deltatime)
{
	SceneManager::getInstance()->updateInput(deltatime);
}

void AladdinGame::update(float deltatime)
{
	SceneManager::getInstance()->update(deltatime);
}

void AladdinGame::draw()
{
	this->_spriteHandle->Begin(D3DXSPRITE_ALPHABLEND);

	SceneManager::getInstance()->draw(_spriteHandle);

	this->_spriteHandle->End();
}

void AladdinGame::loadResource()
{
	// Game::init đã gọi hàm này rồi nên không cần gọi lại AladdinGame::loadResource
	// load resource
	SpriteManager::getInstance()->loadResource(_spriteHandle);
	SoundManager::getInstance()->loadSound(Game::hWindow->getWnd());

}


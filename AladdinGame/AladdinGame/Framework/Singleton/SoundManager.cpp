

#include "SoundManager.h"

SoundManager* SoundManager::_instance;

SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::loadSound(HWND hWnd)
{
	// Khởi tạo CSoundManager.
	DirectSound_Init(hWnd);

	CSound* sound = nullptr;

	sound = LoadSound("Resources//Sounds//map1.wav");
	_listSound[eSoundId::BACKGROUND_STAGE1] = sound;

	sound = LoadSound("Resources//Sounds//HighSword.wav");
	_listSound[eSoundId::sALADDIN_SLASH] = sound;

	sound = LoadSound("Resources//Sounds//AladdinHurt.wav");
	_listSound[eSoundId::sALADDIN_HURT] = sound;

	sound = LoadSound("Resources//Sounds//ObjectThrow.wav");
	_listSound[eSoundId::sOBJECT_THROW] = sound;
}

bool SoundManager::IsPlaying(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}

void SoundManager::Play(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		PlaySound(sound);
		this->currentSound = sound;
	}
}
void SoundManager::PlayLoop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}
void SoundManager::Stop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

SoundManager::SoundManager()
{
	currentSound = nullptr;
}

SoundManager::~SoundManager()
{
}
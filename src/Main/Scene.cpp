#include "pch.h"
#include "Scene.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "GameManager.h"
#include "AssetManager.h"
#include "AudioManager.h"

int Scene::GetWindowWidth() const
{
	return mpGameManager->mWindowWidth;
}

int Scene::GetWindowHeight() const
{
	return mpGameManager->mWindowHeight;
}

float Scene::GetDeltaTime() const
{
	return mpGameManager->mDeltaTime;
}

AssetManager& Scene::GetAssetManager()
{
	return GameManager::Get()->GetAssetManager();
}

LEMusic* Scene::CreateMusic(const char* musicPath, AudioManager& audioManager, int volume)
{
	LEMusic* music = AudioManager::Get()->GetMusic(musicPath);
	music->SetVolume(volume);

	return music;
}

LESound* Scene::CreateSound(const char* soundPath, AudioManager& audioManager, int volume)
{
	LESound* sound = AudioManager::Get()->GetSound(soundPath);
	sound->SetVolume(volume);
	return sound;
}

LERect* Scene::CreateRect(float width, float height)
{
	LERect* newEntity = new LERect(width, height);

	mpGameManager->mRectToAdd.push_back(newEntity);

	return newEntity;
}

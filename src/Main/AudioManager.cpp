#include "pch.h"
#include "AudioManager.h"

LEMusic* AudioManager::LoadMusic(const char* path)
{
	LEMusic* music = new LEMusic();
	music->Load(path);
	//if (!)
	{
		std::cout << "Music : " << path << std::endl;
	}

	mMusic[path] = music;
	return music;
}

LESound* AudioManager::LoadSound(const char* path)
{
	LESound* sound = new LESound();
	sound->Load(path);
	//if (!)
	{
		std::cout << "Sound : " << path << std::endl;
	}

	mSound[path] = sound;
	return sound;
}

LEMusic* AudioManager::GetMusic(const char* path)
{
	auto it = mMusic.find(path);

	if (it == mMusic.end())
	{
		return LoadMusic(path);
	}

	return it->second;
}

LESound* AudioManager::GetSound(const char* path)
{
	auto it = mSound.find(path);

	if (it == mSound.end())
	{
		return LoadSound(path);
	}

	return it->second;
}

AudioManager* AudioManager::Get()
{
	static AudioManager mInstance;

	return &mInstance;
}

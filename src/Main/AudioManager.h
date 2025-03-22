#pragma once
#include "LE.h"
#include <iostream>
#include <map>

class AudioManager
{
	std::map<const char*, LEMusic*> mMusic;
	std::map<const char*, LESound*> mSound;
private:
	LEMusic* LoadMusic(const char* path);
	LESound* LoadSound(const char* path);
public:
	LEMusic* GetMusic(const char* path);
	LESound* GetSound(const char* path);
	static AudioManager* Get();
};


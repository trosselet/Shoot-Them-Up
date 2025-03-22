#pragma once

#include "LE.h"
#include <map>

class AssetManager
{
	std::map<const char*, LETexture*> mTextures;
private:
	LETexture* LoadTexture(const char* path);
public:
	LETexture* GetTexture(const char* path);
	static AssetManager* Get();
};


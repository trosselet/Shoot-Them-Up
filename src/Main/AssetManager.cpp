#include "pch.h"
#include "AssetManager.h"
#include "LE.h"

LETexture* AssetManager::LoadTexture(const char* path)
{
	LETexture* pTexture = new LETexture();
	(*pTexture).Load(path);

	mTextures[path] = pTexture;
	return pTexture;
}

LETexture* AssetManager::GetTexture(const char* path)
{
	auto it = mTextures.find(path);

	if (it == mTextures.end())
	{
		return LoadTexture(path);
	}

	return it->second;
}

AssetManager* AssetManager::Get()
{
	static AssetManager mInstance;

	return &mInstance;
}

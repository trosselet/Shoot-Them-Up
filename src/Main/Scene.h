#pragma once

class GameManager;
class AssetManager;
class AudioManager;
#include "LE.h"
#include <map>

class Scene
{
private:
	GameManager* mpGameManager;
	std::map<const char*, std::vector<LESprite*>> mEntities;

private:
	void SetGameManager(GameManager* pGameManager) { mpGameManager = pGameManager; }
	
protected:
	Scene() = default;

	virtual void OnInitialize() = 0;
	virtual void OnUpdate() = 0;

public:
	template<typename T>
	T* CreateEntity(const char* texturePath, AssetManager& assetManager, int layer);
	
	virtual void OnEvent() = 0;

	float GetDeltaTime() const;
	AssetManager& GetAssetManager();

	LEMusic* CreateMusic(const char* musicPath, AudioManager& audioManager, int volume = 100);
	LESound* CreateSound(const char* soundPath, AudioManager& audioManager, int volume = 100);

	LERect* CreateRect(float width, float height);

	int GetWindowWidth() const;
	int GetWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"
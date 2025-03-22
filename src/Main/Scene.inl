#pragma once

#include "Scene.h"
#include "GameManager.h"
#include "LE.h"
#include "AssetManager.h"

template<typename T>
T* Scene::CreateEntity(const char* texturePath, AssetManager& assetManager, int layer)
{
	static_assert(std::is_base_of<LESprite, T>::value, "T must be derived from LESprite");

	T* newEntity = new T();

	LETexture* tex = AssetManager::Get()->GetTexture(texturePath);

	LESprite* entity = newEntity;
	entity->Initialize();
	entity->SetTexture(tex);
	entity->SetPosition(0, 0);
	entity->SetLayer(layer);

	mpGameManager->mEntitiesToAdd.push_back(newEntity);

	return newEntity;
}
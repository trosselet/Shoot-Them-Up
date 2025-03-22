#include "pch.h"
#include "GameManager.h"
#include "LE.h"
#include "AssetManager.h"
#include "SpriteAnimator.h"
#include "AudioManager.h"
#include <iostream>
#include <chrono>

GameManager::GameManager()
{
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;
}

GameManager* GameManager::Get()
{
	static GameManager mInstance;

	return &mInstance;
}

GameManager::~GameManager()
{
	delete mpWindow;
	delete mpScene;

	for (auto& layer : mSprites)
	{
		for (auto& sprite : layer)
		{
			delete sprite;
		}
		layer.clear();
	}

	mSprites.clear();
}

void GameManager::Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const char* title)
{
	_ASSERT(mpWindow == nullptr);
	mpWindow = new LEWindow();
	mpWindow->Initialize(hInstance, width, height, title);

	LETexture* pTexture = new LETexture();

	mWindowTitle = title;
	mWindowWidth = width;
	mWindowHeight = height;

	mAssetManager = AssetManager::Get();
}

//void GameManager::SetFullScreen()
//{
//	if (!mpWindow)
//	{
//		std::cout << "Window not initialized yet. Cannot toggle fullscreen mode." << std::endl;
//		return;
//	}
//
//	fullScreen = !fullScreen;
//	delete mpWindow;
//
//	if (fullScreen)
//	{
//		mpWindow = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), mWindowTitle, sf::Style::Fullscreen, settings);
//	}
//	else
//	{
//		mpWindow = new sf::RenderWindow(sf::VideoMode(mWindowWidth, mWindowHeight), mWindowTitle, sf::Style::Default, settings);
//	}
//
//	mpWindow->setFramerateLimit(60);
//}

void GameManager::Run()
{
	_ASSERT(mpScene != nullptr);
	_ASSERT(mpWindow != nullptr);

	
	
	auto lastTime = std::chrono::system_clock::now();

	while (mpWindow->IsOpen())
	{
		auto currentTime = std::chrono::system_clock::now();
		std::chrono::duration<float> deltaTime = currentTime - lastTime;

		SetDeltaTime(deltaTime.count());

		HandleInput();

		Update();
		
		Draw();

		lastTime = currentTime;
	}
}

void GameManager::HandleInput()
{
	mEvent.Event(mpWindow, mpScene);
}

void GameManager::Update()
{
	mpScene->OnUpdate();

	if (mCurrentUIState == UIState::Game)
	{
		HandleParallax();

		for (auto layerIt = mSprites.begin(); layerIt != mSprites.end(); ++layerIt)
		{
			for (auto spriteIt = layerIt->begin(); spriteIt != layerIt->end(); )
			{
				LESprite* sprite = *spriteIt;

				sprite->Update();

				if (sprite->ToDestroy())
				{
					mEntitiesToDestroy.push_back(sprite);
					spriteIt = layerIt->erase(spriteIt);
				}
				else
				{
					++spriteIt;
				}
			}
		}

		mAccumulatedDt += GetDeltaTime();
		while (mAccumulatedDt >= FIXED_DT)
		{
			FixedUpdate();
			mAccumulatedDt -= FIXED_DT;
		}
	}

	//Destroy

	for (LESprite* sprite : mEntitiesToDestroy)
	{
		std::cout << "Destroying entity: " << sprite << std::endl;
		delete sprite;
	}
	mEntitiesToDestroy.clear();

	//Sprites

	for (LESprite* sprite : mEntitiesToAdd)
	{
		int layer = sprite->GetLayer();

		while (mSprites.size() <= layer)
		{
			mSprites.emplace_back();
		}

		auto it = std::next(mSprites.begin(), layer);
		it->push_back(sprite);
	}
	mEntitiesToAdd.clear();

	for (auto& layer : mSprites)
	{
		layer.erase(std::remove_if(layer.begin(), layer.end(), [](LESprite* s) { return s == nullptr; }), layer.end());
	}

	//Debug Rect

	for (IObject* rect : mRectToAdd)
	{
		mRects.emplace_back(rect);
	}
	mRectToAdd.clear();
}

void GameManager::FixedUpdate()
{
	for (auto& layer : mSprites)
	{
		for (auto& sprite : layer)
		{
			sprite->FixedUpdate();
		}
	}

	// Collisions
	for (auto layerIt1 = mSprites.begin(); layerIt1 != mSprites.end(); ++layerIt1)
	{
		for (auto layerIt2 = layerIt1; layerIt2 != mSprites.end(); ++layerIt2)
		{
			if (layerIt2 == layerIt1)
				continue;

			for (auto& sprite1 : *layerIt1)
			{
				for (auto& sprite2 : *layerIt2)
				{
					if (sprite1->IsColliding(sprite2))
					{
						sprite1->OnCollision(sprite2);
						sprite2->OnCollision(sprite1);
					}
				}
			}
		}
	}
}

void GameManager::Draw()
{
	mpWindow->Clear();

	for (auto& layer : mSprites)
	{
		for (auto& sprite : layer)
		{
			mpWindow->Draw(sprite);
		}
	}

	for (auto& rect : mRects)
	{
		mpWindow->Draw(rect);
	}

	if (mUI.find(mCurrentUIState) != mUI.end())
	{
		mpWindow->Draw(mUI[mCurrentUIState]);
	}

	mpWindow->Render();
}

void GameManager::AddParallaxBackground(LETexture* tex, int layer, float speed, float posY)
{
	while (mSprites.size() <= layer)
	{
		mSprites.emplace_back();
	}

	auto it = std::next(mSprites.begin(), layer);

	for (int i = 0; i < 2; i++)
	{
		LESprite* sprite = new LESprite();
		sprite->SetTexture(tex);
		sprite->SetTag(-2000);
		sprite->SetPosition((tex->GetWidth() * i), posY, 0, 0);
		sprite->SetInitSpeed(speed);
		sprite->SetLayer(layer);


		mBg.push_back(sprite);
		it->push_back(sprite);
	}
}

void GameManager::AddUIElement(LETexture* tex, UIState state)
{
	LESprite* sprite = new LESprite();
	sprite->SetTexture(tex);
	sprite->SetTag(-1000);
	sprite->SetPosition(mpWindow->GetWidth() / 2, mpWindow->GetHeight() / 2);

	mUI[state] = sprite;
}

void GameManager::HandleParallax()
{
	for (auto bg : mBg)
	{
		float newX = bg->GetPosition(0, 0).x - (bg->GetSpeed()) * GetDeltaTime();
		float newY = bg->GetPosition(0, 0).y;

		bg->SetPosition(newX, newY, 0, 0);

		if (newX <= -mWindowWidth)
		{
			bg->SetPosition(newX + bg->GetTexture()->GetWidth() * 2, newY, 0, 0);
		}
	}
}
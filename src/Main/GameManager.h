#pragma once

#define FIXED_DT 0.01667f

#include <list>

#include "LE.h"
#include "Generic.h"
#include <unordered_map>

class Scene;
class AssetManager;
class SpriteAnimator;
class AudioManager;

enum UIState
{
	Menu,
	Game,
	Pause,
	Win,
	Loose
};

class GameManager
{
	std::list<LESprite*> mEntitiesToDestroy;
	std::list<LESprite*> mEntitiesToAdd;
	std::list<IObject*> mRectToAdd;

	std::list<std::list<LESprite*>> mSprites;
	std::list<IObject*> mRects;
	std::vector<LESprite*> mBg;
	std::unordered_map<UIState, LESprite*> mUI;

	LEWindow* mpWindow;
	LEEvent mEvent;
	Scene* mpScene;

	AssetManager* mAssetManager;
	AudioManager* mAudioManager;

	float mDeltaTime;
	float mAccumulatedDt = 0.f;

	int mWindowWidth;
	int mWindowHeight;

	const char* mWindowTitle = "";
	bool fullScreen = false;

	UIState mCurrentUIState = UIState::Menu;


private:
	GameManager();

	void Run();
	
	void HandleInput();
	void Update();
	void FixedUpdate();
	void Draw();

	void HandleParallax();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }

	LEWindow* GetWindow() const { return mpWindow; }

public:
	~GameManager();
	static GameManager* Get();

	void Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const char* title);
	/*void SetFullScreen();*/

	void AddParallaxBackground(LETexture* tex, int layer, float speed, float posY);

	void AddUIElement(LETexture* tex, UIState state);

	UIState GetUICurrentState() { return mCurrentUIState; }
	void SetUIState(UIState state) { mCurrentUIState = state; }

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	AssetManager& GetAssetManager() { return *mAssetManager; }
	AssetManager* GetAssetManagerT() { return mAssetManager; }
	AudioManager& GetAudioManager() { return *mAudioManager; }
	Scene* GetScene() const { return mpScene; }

	friend Scene;
	friend class SpriteAnimator;
	friend class IObject;
};

#include "GameManager.inl"
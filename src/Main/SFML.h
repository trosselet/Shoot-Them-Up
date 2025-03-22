#pragma once

#include "Generic.h"
#include <SFML/Audio.hpp>

#include <unordered_map>


#include <Windows.h>


class Scene;
class AssetManager;

namespace sf 
{
	class RenderWindow;

	class Drawable;
	class Transformable;
	class Texture;
	class Sprite;
	class CircleShape;
	class Font;
	class Music;
	class Sound;
	class SoundBuffer;
	class RectangleShape;
}

class SFMLWindow : public IWindow
{
	sf::RenderWindow* mpWindow;
	inline static SFMLWindow* mpInstance = nullptr;

	int mwidth = 0, mheight = 0;

public:
	virtual void Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const char* title) override;
	virtual void Clear() override;
	virtual void Draw(IObject* pObject) override;
	virtual void Render() override;
	virtual bool IsOpen() override;

	sf::RenderWindow& GetWindow();

	int GetWidth() { return mwidth; }
	int GetHeight() { return mheight; }

	static SFMLWindow* Get() { return mpInstance; }

	friend class SFMLSprite;
};

class SFMLObject : public IObject
{
protected:

	struct Target
	{
		Vector2<int> position;
		float distance;
		bool isSet = false;
	};

	sf::Drawable* mpDrawable;
	sf::Transformable* mpTransformable;
	bool mToDestroy = false;
	const char* mTexturePath;
	float mSpeed;
	int mWidth = 0, mHeight = 0;
	Vector2<float> mDirection;
	Target mTarget;

	int mLayer;
	int mTag;

public:
	const sf::Drawable& Get() { return *mpDrawable; }

	void Destroy() override;
	bool ToDestroy() override;

	void SetInitSpeed(float speed) override;
	void SetSpeed(float speed) override;
	float GetSpeed() override;

	void SetTag(int tag) override;
	int GetTag() override;
	bool IsTag(int tag) override;

	void SetLayer(int layer) override { mLayer = layer; }
	int GetLayer() override { return mLayer; }

	float GetDeltaTime() const override;
	Scene* GetScene() const override;
	AssetManager& GetAssetManager() override;
};

class SFMLTexture : public ITexture
{
	sf::Texture* mpTexture;

public:
	SFMLTexture();

	void Load(const char* path) override;
	int GetWidth() override;
	int GetHeight() override;

	const sf::Texture& Get() { return *mpTexture; }
};

class SFMLSprite : public ISprite, public SFMLObject
{
	SFMLTexture* pSFMLTexture;

public:
	SFMLSprite();

	void SetTexture(ITexture* pTexture) override;

	ITexture* GetTexture() const override { return pSFMLTexture; }

	void SetPosition(float x, float y, float offsetX = 0.5, float offsetY = 0.5) override;
	Vector2<float> GetPosition(float offsetX = 0.5, float offsetY = 0.5) const override;

	void SetDirection(float x, float y, float speed = -1.f) override;
	void SetDirectionX(float x, float speed) override;
	void SetDirectionY(float y, float speed) override;

	bool IsColliding(ISprite* other) const;
	bool IsInside(float x, float y) const;

	bool GoToDirection(int x, int y, float speed = -1.f) override;
	bool GoToPosition(int x, int y, float speed = -1.f) override;

protected:
	virtual void OnCollision(SFMLSprite* collidedWith) {}
	virtual void OnUpdate() {}
	virtual void OnFixedUpdate() {}
	virtual void OnInitialize() {}

private:
	void Update() override;
	void FixedUpdate() override;
	void Initialize() override;
	friend class GameManager;
	friend Scene;
};

class SFMLCircle : public ICircle, public SFMLObject
{
public:
	SFMLCircle();

	void SetRadius(float radius) override;
	void SetColor(unsigned char r, unsigned char g, unsigned char b) override;
};

class SFMLRect : public IRectangle, public SFMLObject
{
public:
	SFMLRect(float x, float y);
	void SetSize(float x, float y) override;
	void SetPosition(Vector2<float> position) override;
	void SetColor(unsigned char r, unsigned char g, unsigned char b) override;
};

class SFMLFont : public IPersonalFont
{
	sf::Font* mFont;

public:
	SFMLFont();
};

class SFMLEvent : public IEvent
{
public:
	void Event(SFMLWindow* mpWindow, Scene* mpScene);
};

class SFMLInput : public IInput
{
private:
	std::unordered_map<std::string, sf::Keyboard::Key> m_keyMapping;
	std::unordered_map<std::string, KeyState> m_keyStates;
	std::unordered_map<int, KeyState> m_mouseButtonStates;

public:
	SFMLInput();
	void MapKey(const std::string& keyName, int engineKeyCode) override;
	void Update() override;
	KeyState GetKeyState(const std::string& keyName) const override;
	KeyState GetMouseButtonState(int buttonID) const override;
};

class SFMLMusic : public IAudio
{
	sf::Music* mMusic = nullptr;

public:
	SFMLMusic();
	~SFMLMusic();

	void Play() override;
	void Load(const char* path) override;
	void SetVolume(int volume) override;
	void Stop() override;
	void Pause() override;
};

class SFMLSound : public IAudio
{
	sf::Sound* mSound = nullptr;
	sf::SoundBuffer* mBuffer = nullptr;

public:
	SFMLSound();
	~SFMLSound();

	void Play() override;
	void Load(const char* path) override;
	void SetVolume(int volume) override;
	void Stop() override;
	void Pause() override;
};


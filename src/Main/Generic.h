#pragma once
#include "Vector2.h"
#include <string>

#include <Windows.h>

class IObject;
class AssetManager;
class Scene;

enum KeyState {
	NONE,  // NOT PRESSED
	STAY,  // STAY PRESSED
	UP,    // RELEASED
	DOWN   // PRESSED ONCE
};

class IWindow
{
public:
	virtual void Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const char* title) = 0;
	virtual void Clear() = 0;
	virtual void Draw(IObject* pDrawable) = 0;
	virtual void Render() = 0;
	virtual bool IsOpen() = 0;
};


class ITexture
{
public:
	virtual void Load(const char* path) = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
};

class IObject
{
	virtual void Destroy() = 0;
	virtual bool ToDestroy() = 0;

	virtual void SetInitSpeed(float speed) = 0;
	virtual void SetSpeed(float speed) = 0;
	virtual float GetSpeed() = 0;

	virtual void SetTag(int tag) = 0;
	virtual int GetTag() = 0;
	virtual bool IsTag(int tag) = 0;

	virtual void SetLayer(int layer) = 0;
	virtual int GetLayer() = 0;

	virtual float GetDeltaTime() const = 0;
	virtual Scene* GetScene() const = 0;
	virtual AssetManager& GetAssetManager() = 0;
};

class ISprite
{
public:
	virtual void SetTexture(ITexture* pTexture) = 0;
	virtual void SetPosition(float x, float y, float offsetX = 0.5, float offsetY = 0.5) = 0;
	virtual Vector2<float> GetPosition(float offsetX = 0.5, float offsetY = 0.5) const = 0;

	virtual void SetDirection(float x, float y, float speed = -1.f) = 0;
	virtual void SetDirectionX(float x, float speed) = 0;
	virtual void SetDirectionY(float y, float speed) = 0;

	virtual ITexture* GetTexture() const = 0;
	virtual bool IsColliding(ISprite* other) const = 0;
	virtual bool IsInside(float x, float y) const = 0;

	virtual bool GoToDirection(int x, int y, float speed = -1.f) = 0;
	virtual bool GoToPosition(int x, int y, float speed = -1.f) = 0;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Initialize() = 0;
};

class ICircle
{
public:
	virtual void SetRadius(float radius) = 0;
	virtual void SetColor(unsigned char r, unsigned char g, unsigned char b) = 0;
};

class IRectangle
{
public:
	virtual void SetSize(float x, float y) = 0;
	virtual void SetPosition(Vector2<float> position) = 0;
	virtual void SetColor(unsigned char r, unsigned char g, unsigned char b) = 0;
};

class IPersonalFont
{
};

class IEvent
{
};

class IInput
{
public:
	virtual void MapKey(const std::string& keyName, int engineKeyCode) = 0;
	virtual KeyState GetKeyState(const std::string& keyName) const = 0;
	virtual KeyState GetMouseButtonState(int buttonID) const = 0;
	virtual void Update() = 0;
};

class IAudio
{
	virtual void Play() = 0;
	virtual void Load(const char* path) = 0;
	virtual void SetVolume(int volume) = 0;
	virtual void Stop() = 0;
	virtual void Pause() = 0;
};
#include "pch.h"
#include "SFML.h"
#include "Scene.h"
#include "AssetManager.h"
#include <SFML/Graphics.hpp>

#include <Windows.h>


void SFMLWindow::Initialize(HINSTANCE hInstance, unsigned int width, unsigned int height, const char* title)
{
	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), "SFML works!");

	mwidth = width;
	mheight = height;
}

void SFMLWindow::Clear()
{
	mpWindow->clear();
}

void SFMLWindow::Draw(IObject* pDrawable)
{
	SFMLObject* pSFMLDrawable = (SFMLObject*)pDrawable;
	mpWindow->draw(pSFMLDrawable->Get());
}

void SFMLWindow::Render()
{
	mpWindow->display();
}

bool SFMLWindow::IsOpen()
{
	return mpWindow->isOpen();
}

sf::RenderWindow& SFMLWindow::GetWindow()
{
	return *mpWindow;
}

void SFMLObject::Destroy()
{
	mToDestroy = true;
}

bool SFMLObject::ToDestroy()
{
	return mToDestroy;
}

void SFMLObject::SetInitSpeed(float speed)
{
	mSpeed = speed;
}

void SFMLObject::SetSpeed(float speed)
{
	mSpeed = speed;
}

float SFMLObject::GetSpeed()
{
	return mSpeed;
}

void SFMLObject::SetTag(int tag)
{
	mTag = tag;
}

int SFMLObject::GetTag()
{
	return mTag;
}

bool SFMLObject::IsTag(int tag)
{
	_ASSERT(this != nullptr);
	return mTag == tag;
}

float SFMLObject::GetDeltaTime() const
{
	float deltaTime = GameManager::Get()->GetDeltaTime();
	return deltaTime;
}

Scene* SFMLObject::GetScene() const
{
	return GameManager::Get()->GetScene();
}

AssetManager& SFMLObject::GetAssetManager()
{
	return GameManager::Get()->GetAssetManager();
}

SFMLSprite::SFMLSprite()
{
	sf::Sprite* pSprite = new sf::Sprite();
	
	mpDrawable = pSprite;
	mpTransformable = pSprite;
}

void SFMLSprite::SetTexture(ITexture* pTexture)
{
	pSFMLTexture = (SFMLTexture*)pTexture;
	_ASSERT(pSFMLTexture, "Entity texture doesn't load !");
	((sf::Sprite*)mpDrawable)->setTexture(pSFMLTexture->Get());
}

void SFMLSprite::SetPosition(float x, float y, float offsetX, float offsetY)
{
	float adjustedX = x - (pSFMLTexture->GetWidth() * offsetX);
	float adjustedY = y - (pSFMLTexture->GetHeight() * offsetY);
	mpTransformable->setPosition(adjustedX, adjustedY);
}


Vector2<float> SFMLSprite::GetPosition(float offsetX, float offsetY) const
{
	float originalX = mpTransformable->getPosition().x + (pSFMLTexture->GetWidth() * offsetX);
	float originalY = mpTransformable->getPosition().y + (pSFMLTexture->GetHeight() * offsetY);
	return Vector2<float>(originalX, originalY);
}

void SFMLSprite::SetDirection(float x, float y, float speed)
{
	if (speed > 0)
		SetSpeed(speed);

	mDirection = Vector2<float>(x, y);

	mDirection.Normalize();
}

void SFMLSprite::SetDirectionX(float x, float speed)
{
	SetDirection(x, mDirection.y, speed);
}

void SFMLSprite::SetDirectionY(float y, float speed)
{
	SetDirection(mDirection.x, y, speed);
}


bool SFMLSprite::IsColliding(ISprite* other) const
{
	Vector2<float> position = GetPosition();
	float width = pSFMLTexture->GetWidth();
	float height = pSFMLTexture->GetHeight();

	auto otherPosition = other->GetPosition();
	float otherWidth = other->GetTexture()->GetWidth();
	float otherHeight = other->GetTexture()->GetHeight();

	return (position.x < otherPosition.x + otherWidth &&
		position.x + width > otherPosition.x &&
		position.y < otherPosition.y + otherHeight &&
		position.y + height > otherPosition.y
		);
}

bool SFMLSprite::IsInside(float x, float y) const
{
	return (x >= GetPosition().x && x <= GetPosition().x + pSFMLTexture->GetWidth() &&
		y >= GetPosition().y && y <= GetPosition().y + pSFMLTexture->GetHeight());
}

bool SFMLSprite::GoToDirection(int x, int y, float speed)
{
	if (speed > 0)
		SetSpeed(speed);

	Vector2<float> position = GetPosition();
	Vector2<float> direction = Vector2<float>(x - position.x, y - position.y);

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude != 0)
	{
		direction.x /= magnitude;
		direction.y /= magnitude;
	}
	else
	{
		return false;
	}

	mDirection = direction;

	return true;
}

bool SFMLSprite::GoToPosition(int x, int y, float speed)
{
	if (GoToDirection(x, y, speed) == false)
		return false;

	Vector2<float> position = GetPosition();

	mTarget.position = { x, y };
	float newX = position.x - x;
	float newY = position.y - y;
	mTarget.distance = std::sqrt(newX * newX + newY * newY);
	mTarget.isSet = true;

	return true;
}

void SFMLSprite::Update()
{

	float dt = GameManager::Get()->GetDeltaTime();
	float distance = dt * mSpeed;
	Vector2<float> translation = mDirection * distance;
	SetPosition(GetPosition().x + translation.x, GetPosition().y + translation.y);

	if (mTarget.isSet)
	{

		if (mTarget.distance <= distance)
		{
			SetPosition(mTarget.position.x, mTarget.position.y);
			mDirection = Vector2<float>(0.f, 0.f);
			mTarget.isSet = false;
		}
		else
		{
			mTarget.distance -= distance;
		}

	}


	OnUpdate();
}

void SFMLSprite::FixedUpdate()
{
	OnFixedUpdate();
}

void SFMLSprite::Initialize()
{
	if (pSFMLTexture)
	{
		mWidth = pSFMLTexture->GetWidth();
		mHeight = pSFMLTexture->GetHeight();
	}
	OnInitialize();
}

SFMLTexture::SFMLTexture()
{
	mpTexture = new sf::Texture();
}

void SFMLTexture::Load(const char* path)
{
	mpTexture->loadFromFile(std::string(path) + ".png");
}

int SFMLTexture::GetWidth()
{
	return mpTexture->getSize().x;
}

int SFMLTexture::GetHeight()
{
	return mpTexture->getSize().y;
}

SFMLCircle::SFMLCircle()
{
	sf::CircleShape* pCircle = new sf::CircleShape();

	mpDrawable = pCircle;
	mpTransformable = pCircle;
}

void SFMLCircle::SetRadius(float radius)
{
	((sf::CircleShape*)mpDrawable)->setRadius(radius);
}

void SFMLCircle::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	((sf::CircleShape*)mpDrawable)->setFillColor(sf::Color(r, g, b));
}

SFMLFont::SFMLFont()
{
	mFont = new sf::Font();
	mFont->loadFromFile("../../res/Hack-Regular.ttf");
	_ASSERT(mFont);
}

void SFMLEvent::Event(SFMLWindow* mpWindow, Scene* mpScene)
{
	sf::Event event;
	while (mpWindow->GetWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mpWindow->GetWindow().close();
		}
		mpScene->OnEvent();
	}
}

SFMLInput::SFMLInput()
{
	MapKey("A", sf::Keyboard::A);
	MapKey("Z", sf::Keyboard::Z);
	MapKey("Q", sf::Keyboard::Q);
	MapKey("S", sf::Keyboard::S);
	MapKey("D", sf::Keyboard::D);
	MapKey("E", sf::Keyboard::E);
	MapKey("P", sf::Keyboard::P);
	MapKey("Space", sf::Keyboard::Space);
	MapKey("Enter", sf::Keyboard::Enter);
}

void SFMLInput::MapKey(const std::string& keyName, int engineKeyCode)
{
	m_keyMapping[keyName] = static_cast<sf::Keyboard::Key>(engineKeyCode);
	m_keyStates[keyName] = KeyState::NONE;
}

void SFMLInput::Update()
{
	for (auto& [keyName, sfKey] : m_keyMapping) {
		KeyState& state = m_keyStates[keyName];
		bool isCurrentlyPressed = sf::Keyboard::isKeyPressed(sfKey);

		if (isCurrentlyPressed) {
			if (state == KeyState::NONE || state == KeyState::UP) {
				state = KeyState::DOWN;
			}
			else if (state == KeyState::DOWN || state == KeyState::STAY) {
				state = KeyState::STAY;
			}
		}
		else {
			if (state == KeyState::STAY || state == KeyState::DOWN) {
				state = KeyState::UP;
			}
			else if (state == KeyState::UP) {
				state = KeyState::NONE;
			}
		}
	}

	for (auto& [button, state] : m_mouseButtonStates) {
		bool isCurrentlyPressed = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));

		if (isCurrentlyPressed) {
			if (state == KeyState::NONE || state == KeyState::UP) {
				state = KeyState::DOWN;
			}
			else if (state == KeyState::DOWN || state == KeyState::STAY) {
				state = KeyState::STAY;
			}
		}
		else {
			if (state == KeyState::STAY || state == KeyState::DOWN) {
				state = KeyState::UP;
			}
			else if (state == KeyState::UP) {
				state = KeyState::NONE;
			}
		}
	}
}
KeyState SFMLInput::GetKeyState(const std::string& keyName) const
{
	auto it = m_keyStates.find(keyName);
	if (it != m_keyStates.end())
	{
		return it->second;
	}
	else
	{
		return KeyState::NONE;
	}
}

KeyState SFMLInput::GetMouseButtonState(int buttonID) const
{
	auto it = m_mouseButtonStates.find(buttonID);
	if (it != m_mouseButtonStates.end())
	{
		return it->second;
	}
	else
	{
		return KeyState::NONE;
	}
}

SFMLMusic::SFMLMusic()
{
	mMusic = new sf::Music();
}

SFMLMusic::~SFMLMusic()
{
	delete mMusic;
}

void SFMLMusic::Play()
{
	mMusic->play();
}

void SFMLMusic::Load(const char* path)
{
	mMusic->openFromFile(path);
}

void SFMLMusic::SetVolume(int volume)
{
	mMusic->setVolume(volume);
}

void SFMLMusic::Stop()
{
	mMusic->stop();
}

void SFMLMusic::Pause()
{
	mMusic->pause();
}

SFMLSound::SFMLSound()
{
	mSound = new sf::Sound();
	mBuffer = new sf::SoundBuffer();
}

SFMLSound::~SFMLSound()
{
	delete mSound;
	delete mBuffer;
}

void SFMLSound::Play()
{
	mSound->play();
}

void SFMLSound::Load(const char* path)
{
	mBuffer->loadFromFile(path);
	mSound->setBuffer(*mBuffer);
}

void SFMLSound::SetVolume(int volume)
{
	mSound->setVolume(volume);
}

void SFMLSound::Stop()
{
	mSound->stop();
}

void SFMLSound::Pause()
{
	mSound->pause();
}

SFMLRect::SFMLRect(float x, float y)
{
	sf::RectangleShape* pRect = new sf::RectangleShape(sf::Vector2f(x, y));
	pRect->setOutlineThickness(3);

	mpDrawable = pRect;
	mpTransformable = pRect;
}

void SFMLRect::SetSize(float x, float y)
{
	return;
}

void SFMLRect::SetPosition(Vector2<float> position)
{
	((sf::RectangleShape*)mpTransformable)->setPosition(position.x - 440 * 0.5f, position.y - 151 * 0.5f);
}

void SFMLRect::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	((sf::RectangleShape*)mpDrawable)->setFillColor(sf::Color::Transparent);
	
	((sf::RectangleShape*)mpDrawable)->setOutlineColor(sf::Color(r, g, b));
}

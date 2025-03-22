#pragma once

#include "LE.h"
#include "GameManager.h"

class SpriteAnimator
{
	struct Animation
	{
		std::vector<LETexture*> textures;
		float spritesDuration;

	};

private:
	

	std::map<const char*, Animation> mAnimations;
	const char* mCurrentAnimationName;
	float mElapsedTime = 0.f;
	int mCurrentFrame = 0;
	LESprite* mpSprite = nullptr;
public:

	SpriteAnimator(LESprite* sprite);
	void CreateAnimation(const char* animName, std::vector<const char*> listCharTexture, float animationTime);
	void SetAnimation(const char* name);
	void Update(float dt);

};


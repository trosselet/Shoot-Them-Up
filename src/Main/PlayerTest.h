#pragma once

#include "LE.h"
#include "SpriteAnimator.h"
#include <iostream>

class PlayerTest : public LESprite
{
	//std::string animName;
	SpriteAnimator* mpSpriteAnimator;

public:
	void OnInitialize() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;
	void OnCollision(LESprite* collidedWith) override;
};


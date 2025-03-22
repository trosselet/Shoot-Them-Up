#include "pch.h"
#include "PlayerTest.h"
#include "SpriteAnimator.h"

void PlayerTest::OnInitialize()
{
	mpSpriteAnimator = new SpriteAnimator(this);

	std::vector<const char*> mWalkFrames =
	{
		"../../res/Testing/Textures/player/player00",
		"../../res/Testing/Textures/player/player01",
		"../../res/Testing/Textures/player/player02",
		"../../res/Testing/Textures/player/player03",
		"../../res/Testing/Textures/player/player04",
		"../../res/Testing/Textures/player/player05"
	};

	mpSpriteAnimator->CreateAnimation("Walk", mWalkFrames, 0.1f);
	mpSpriteAnimator->SetAnimation("Walk");

}

void PlayerTest::OnUpdate()
{
	SetDirection(0, 0, 0);
	mpSpriteAnimator->Update(GameManager::Get()->GetDeltaTime());
}

void PlayerTest::OnFixedUpdate()
{
}

void PlayerTest::OnCollision(LESprite* collidedWith)
{
	if (collidedWith->IsTag(5))
	{
		std::cout << "IsTag" << std::endl;
	}
}

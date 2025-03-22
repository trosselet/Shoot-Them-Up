#pragma once
#include "LE.h"
#include "Player.h"
#include "Vector2.h"

class PowerUp : public LESprite
{
	Vector2 <float> mDirection;
	float mSpeed;
	float mBoundaryPadding;

public:

	void OnUpdate()override;
	void OnCollision(LESprite* collidedWith)override;
	void OnInitialize()override;
	float GetSpeed();
	void CheckWindow();

};


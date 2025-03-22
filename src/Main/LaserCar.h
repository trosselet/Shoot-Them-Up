#pragma once
#include "Ennemis.h"
#include "Vector2.h"
#include"LaserProjectile.h"

class Scene;

class LaserCar : public Ennemis
{
	float mCooldownTeleport = 2.0f;
	float mCooldownTeleportTimer;
	std::vector<Vector2<float>> mPositions;
	int mCurrentIndex = 0;
	float mLaserDuration = 1.5f; 
	float mLaserTimer = 0.0f;   
	bool mLaserActive = false;  
	bool initialized = false;
	std::vector<LaserProjectile*> mLaserProjectiles;

public:
	void OnUpdate() override;
	void OnCollision(LESprite* collidedWith) override;
	void OnInitialize() override;
	void CheckWindow();
	float GetSpeed();
	void FireLaser();
	void DestroyLaser();
};


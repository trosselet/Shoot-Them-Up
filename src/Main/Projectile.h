#pragma once
#include "LE.h"
#include "SpriteAnimator.h"


class Projectile : public LESprite
{
private:

	SpriteAnimator* mpSpriteAnimator;

	int mDamage = 1;
	float mShootCooldown = 1.0f;
	float mShootCooldownTimer = 0.0f;
	float mDeathCooldown = 4.f;
	float macceleration = 50;
	bool mWasParried = false;
	
public:

	bool mEnnemy = false;

	float GetShootCooldown();
	float GetShootCooldownTimer();
	void SetShootCooldownTimer(float ShootCooldownTimer);
	int GetDamage();
	void SetDamage(int damage);
	float GetSpeed();
	virtual void OnUpdate() override;
	virtual void OnCollision(LESprite* collidedWith) override;
	virtual void OnInitialize() override;
	void CheckWindow();
	void SetParried(bool parried);
	bool WasParried() const;
};


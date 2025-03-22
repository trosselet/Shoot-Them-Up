#include "pch.h"
#include "ProjectileEnnemi.h"

float ProjectileEnnemi::GetShootCooldown()
{
	return mShootCooldown;
}

float ProjectileEnnemi::GetShootCooldownTimer()
{
	return 0.0f;
}

void ProjectileEnnemi::SetShootCooldownTimer(float ShootCooldownTimer)
{
	mShootCooldownTimer = ShootCooldownTimer;
}

int ProjectileEnnemi::GetDamage()
{
	return mDamage;
}

void ProjectileEnnemi::SetDamage(int damage)
{
	mDamage = damage;
}

float ProjectileEnnemi::GetSpeed()
{
	return mSpeed;
}

void ProjectileEnnemi::OnUpdate()
{
	if (IsTag(-6))
	{
		mSpeed += macceleration;
		// SetSpeed(GetSpeed() + macceleration * Time::DeltaTime());

	}
	if (IsTag(-7))
	{
		mSpeed += macceleration / 2;
		//SetSpeed(GetSpeed() - (macceleration / 2) * Time::DeltaTime());
	}

	mDeathCooldown -= GetDeltaTime();
	if (mDeathCooldown <= 0)
	{
		Destroy();
	}

	mpSpriteAnimator->Update(GameManager::Get()->GetDeltaTime());
}

void ProjectileEnnemi::OnCollision(LESprite* collidedWith)
{

}

void ProjectileEnnemi::OnInitialize()
{
	mpSpriteAnimator = new SpriteAnimator(this);

	std::vector<const char*> mTirFrames =
	{
		"../../res/Testing/Proj/1",
		"../../res/Testing/Proj/2",
		"../../res/Testing/Proj/3",
		"../../res/Testing/Proj/4",
		"../../res/Testing/Proj/5",
		"../../res/Testing/Proj/6",
		"../../res/Testing/Proj/7",
		"../../res/Testing/Proj/8",
		"../../res/Testing/Proj/9",
		"../../res/Testing/Proj/10",
		"../../res/Testing/Proj/11",
		"../../res/Testing/Proj/12",
		"../../res/Testing/Proj/13",
		"../../res/Testing/Proj/14",
		"../../res/Testing/Proj/15"
	};
		

	mpSpriteAnimator->CreateAnimation("Shoot", mTirFrames, 0.05f);
	mpSpriteAnimator->SetAnimation("Shoot");
}

void ProjectileEnnemi::CheckWindow()
{
}

void ProjectileEnnemi::SetParried(bool parried)
{
	mWasParried = parried;
}

bool ProjectileEnnemi::WasParried() const
{
	return mWasParried;
}

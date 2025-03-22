#include "pch.h"
#include "Projectile.h"

float Projectile::GetShootCooldown()
{
	return mShootCooldown;
}

float Projectile::GetShootCooldownTimer()
{
	return 0.0f;
}

void Projectile::SetShootCooldownTimer(float ShootCooldownTimer)
{
	mShootCooldownTimer = ShootCooldownTimer;
}

int Projectile::GetDamage()
{
	return mDamage;
}

void Projectile::SetDamage(int damage)
{
	mDamage = damage;
}

float Projectile::GetSpeed()
{
	return mSpeed;
}

void Projectile::OnUpdate()
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

void Projectile::OnCollision(LESprite* collidedWith)
{

}

void Projectile::OnInitialize()
{
	mpSpriteAnimator = new SpriteAnimator(this);

	std::vector<const char*> mTirFrames;

	if (!mEnnemy)
	{
		mTirFrames =
		{
			"../../res/Testing/Proj/Tir0001",
			"../../res/Testing/Proj/Tir0002",
			"../../res/Testing/Proj/Tir0003",
			"../../res/Testing/Proj/Tir0004",
			"../../res/Testing/Proj/Tir0005",
			"../../res/Testing/Proj/Tir0006",
			"../../res/Testing/Proj/Tir0007"
		};
	}
	else
	{
		mTirFrames =
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
	}

	mpSpriteAnimator->CreateAnimation("Shoot", mTirFrames, 0.1f);
	mpSpriteAnimator->SetAnimation("Shoot");
}

void Projectile::CheckWindow()
{
}

void Projectile::SetParried(bool parried)
{
	mWasParried = parried;
}

bool Projectile::WasParried() const
{
	return mWasParried;
}

#include "pch.h"
#include "SpiraleProjectiles.h"


void SpiraleProjectiles::OnInitialize()
{
}

void SpiraleProjectiles::OnUpdate()
{
	mElapsedTime += GetDeltaTime();


	mRadius += mRadiusSpeed * GetDeltaTime();

	mAngle += mAngleSpeed * (1 + mSpacingFactor * mRadius) * GetDeltaTime();

	float newX = 1100 + std::cos(mAngle) * mRadius;
	float newY = 360 + std::sin(mAngle) * mRadius;

	SetPosition(newX, newY);

	if (mRadius >= mMaxDistance)
	{
		Destroy();
	}
}

void SpiraleProjectiles::OnCollision(LESprite* collidedWith)
{
}

float SpiraleProjectiles::GetSpeed()
{
	return mSpeed;
}

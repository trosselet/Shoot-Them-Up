#include "pch.h"
#include "PowerUp.h"

void PowerUp::OnUpdate()
{
	Vector2<float> newPosition = GetPosition() + mDirection * mSpeed * GetDeltaTime();
	SetPosition(newPosition.x, newPosition.y);

	CheckWindow();

}

void PowerUp::OnCollision(LESprite* collidedWith)
{
	if (collidedWith->IsTag(1))
	{
		Destroy();


		Player* player = dynamic_cast<Player*>(collidedWith);
		if (player)
		{
			player->SetTripleShotEnabled(true);
		}
	}

}

void PowerUp::OnInitialize()
{
	float randomX = static_cast<float>(rand() % 100 - 50) / 50.0f;
	float randomY = static_cast<float>(rand() % 100 - 50) / 50.0f;
    Vector2<float> mDirection (randomX, randomY);

	float magnitude = std::sqrt(mDirection.x * mDirection.x + mDirection.y * mDirection.y);
	if (magnitude != 0)
		mDirection /= magnitude;

	mSpeed = 150.f;
	mBoundaryPadding = 10.f;

}

float PowerUp::GetSpeed()
{
    return mSpeed;
}

void PowerUp::CheckWindow()
{
	float constrainedX = std::clamp(this->GetPosition(0.5, 0.5).x, (float)(mWidth / 2), 1920.f - mWidth / 2);
	float constrainedY = std::clamp(this->GetPosition(0.5, 0.5).y, 740.f - mHeight / 2, 1080.f - mHeight / 2);

	SetPosition(constrainedX, constrainedY);
}

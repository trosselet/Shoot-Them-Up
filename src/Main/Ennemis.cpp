#include "pch.h"
#include "Ennemis.h"
#include <iostream>
#include "Projectile.h"
#include "Scene.h"
#include "SampleScene.h"
#include "PowerUp.h"

bool Ennemis::IsAlive() const
{
	return mIsAlive;
}

void Ennemis::OnUpdate()
{

	if (mIsStunned)
	{
		std::cout << "Enemy is stunned. Stun timer: " << mStunTimer << std::endl;
		mStunTimer -= GetDeltaTime();

		SetDirectionX(0.f, 0.f);

		SetDirectionY(0.f, 0.f);

		if (mStunTimer <= 0.f)
		{
			mIsStunned = false;
			mStunTimer = 0.f;
			std::cout << "Enemy stun ended." << std::endl;
		}

		return;
	}
	//IsStunned();

	Shoot();

	static float angle = 90.f; 

	SetDirectionX(-1.f, GetSpeed());

	CheckWindow();

	float amplitude = 200.f; 
	float frequency = 3.5f;  

	angle += frequency * GetDeltaTime(); 
	if (angle > 2 * 3.14159f) 
	{
		angle -= 2 * 3.14159f;
	}

	float offsetY = amplitude * std::sin(angle);
	SetDirectionY(offsetY / GetSpeed(), 300.f); 

	if (GetPosition().x <= -50)
	{
		Destroy();
	}
}

void Ennemis::OnCollision(LESprite* collidedWith)
{
	if (collidedWith->IsTag(-6))
	{
		Projectile* projecollider = dynamic_cast<Projectile*>(collidedWith);

		if (projecollider)
		{
			mLife -= projecollider->GetDamage();

			if (projecollider->WasParried())
			{

				Stun(3.0f);
				std::cout << "Stun called with duration: 3.0f" << std::endl;
				mLife -= projecollider->GetDamage();
			}
			projecollider->Destroy();

			if (mLife <= 0)
			{
				PowerUp* powercoll = dynamic_cast<PowerUp*>(collidedWith);
				Destroy();

				powercoll = GetScene()->CreateEntity<PowerUp>(("../../res/Testing/UI/Bonus"), GetAssetManager(), 8);
				powercoll->SetPosition(960, 540);
				powercoll->SetSpeed(200.f);
				powercoll->SetTag(6);
			}
		}
	}
}

void Ennemis::OnInitialize()
{
	
}

void Ennemis::CheckWindow()
{
	if (GetPosition().x < -100)
	{
		Destroy();
	}

	float constrainedY = std::clamp(this->GetPosition().y, 740.f - mHeight / 2, 1080.f - mHeight / 2);

	SetPosition(GetPosition().x, constrainedY);
}

float Ennemis::GetSpeed()
{
	return mSpeed;
}

void Ennemis::Shoot()
{
	mShootCooldownEnnemisTimer += GetDeltaTime();
	if (mShootCooldownEnnemisTimer > 3.0f)
	{
		if (GetPosition().x <= 1920)
		{
			projectileEnnemis = GetScene()->CreateEntity<ProjectileEnnemi>(("../../res/Testing/Proj/15"), GetAssetManager(), 8);
			projectileEnnemis->SetPosition(GetPosition().x, GetPosition().y);
			projectileEnnemis->SetDirection(-1.0f, 0.f, projectileEnnemis->GetSpeed());
			projectileEnnemis->SetTag(-7);
			mSampleScene->AddProjectile(projectileEnnemis);

			mShootCooldownEnnemisTimer = 0.f;
		}
	}
}

void Ennemis::Stun(float duration)
{
	mIsStunned = true;
	mStunTimer = duration;
}

void Ennemis::IsStunned()
{
	if (mIsStunned)
	{
		std::cout << "Enemy is stunned. Stun timer: " << mStunTimer << std::endl;
		mStunTimer -= GetDeltaTime();

		SetDirectionX(0.f, 0.f);

		SetDirectionY(0.f, 0.f);

		if (mStunTimer <= 0.f)
		{
			mIsStunned = false;
			mStunTimer = 0.f;
			std::cout << "Enemy stun ended." << std::endl;
		}

		return;
	}

}

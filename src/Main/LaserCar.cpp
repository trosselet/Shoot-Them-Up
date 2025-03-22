#include "pch.h"
#include "LaserCar.h"
#include "Scene.h"
#include <iostream>
#include "LaserProjectile.h"

void LaserCar::OnUpdate()
{
    if (!initialized)
    {
      
        mPositions.push_back(Vector2<float>(GetScene()->GetWindowWidth() - 100, 740.f)); // Haut
        mPositions.push_back(Vector2<float>(GetScene()->GetWindowWidth() - 100, 870.f)); // Milieu
        mPositions.push_back(Vector2<float>(GetScene()->GetWindowWidth() - 100, 1000.f)); // Bas

        if (!mPositions.empty())
        {
            mCurrentIndex = rand() % mPositions.size();
            SetPosition(mPositions[mCurrentIndex].x, mPositions[mCurrentIndex].y);
        }
        else
        {
            SetPosition(0.f, 0.f);
        }

        initialized = true;
        return;
    }

    mCooldownTeleportTimer += GetDeltaTime();

    if (mCooldownTeleportTimer >= mCooldownTeleport)
    {
        mCooldownTeleportTimer = 0.0f;

        int newIndex;
        do
        {
            newIndex = rand() % mPositions.size();
        } while (newIndex == mCurrentIndex); 

        mCurrentIndex = newIndex;

        
        SetPosition(mPositions[mCurrentIndex].x, mPositions[mCurrentIndex].y);
        FireLaser();
        mLaserActive = true;
        mLaserTimer = 0.0f;
    }
    if (mLaserActive)
    {
        mLaserTimer += GetDeltaTime();

        if (mLaserTimer >= mLaserDuration || !IsAlive())
        {
            DestroyLaser();
        }
    }
}

void LaserCar::OnCollision(LESprite* collidedWith)
{
    if (collidedWith->IsTag(-6))
    {
        Projectile* projecollider = dynamic_cast<Projectile*>(collidedWith);

        if (projecollider)
        {
            std::cout << "oui" << std::endl;

            mLife -= projecollider->GetDamage();
            projecollider->Destroy();
            if (mLife <= 0)
            {

                mIsAlive = false;

                Destroy();
            }
        }
    }
}

void LaserCar::OnInitialize()
{
}

void LaserCar::CheckWindow()
{
    float constrainedY = std::clamp(this->GetPosition().y, 740.f - mHeight / 2, 1000.f);

    SetPosition(GetPosition().x, constrainedY);
}

float LaserCar::GetSpeed()
{
	return mSpeed;
}

void LaserCar::FireLaser()
{
    const int numParts = 5; 
    const float spacing = 30.0f; 
    const Vector2<float> startPos = GetPosition();
    const Vector2<float> direction(-1.0f, 0.0f);

    mLaserProjectiles.clear(); 

    for (int i = 0; i < numParts; ++i)
    {
        LaserProjectile* laser = GetScene()->CreateEntity<LaserProjectile>("../../res/Testing/Proj/Tir0001", GetAssetManager(), 9);
        if (laser)
        {
            Vector2<float> position = startPos + direction * (spacing * i);
            laser->SetPosition(position.x, position.y);
            
            laser->SetDamage(laser->GetDamage());
    
            mLaserProjectiles.push_back(laser);
        }
    }
}

void LaserCar::DestroyLaser()
{
    for (LaserProjectile* laser : mLaserProjectiles)
    {
        if (laser)
        {
            laser->Destroy(); 
        }
    }

    mLaserProjectiles.clear(); 
    mLaserActive = false;
}

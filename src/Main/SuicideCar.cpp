#include "pch.h"
#include "SuicideCar.h"
#include <iostream>

void SuicideCar::OnUpdate()
{

    CheckWindow();
    
    mCooldownSuicideTimer += GetDeltaTime();
   
    Vector2<float> position = GetPosition();
    
    if (mCooldownSuicideTimer < mCooldownSuicide && position.x - 1920 <= 0)
    {
        int windowHeight = 1080;
        
        static float yDirection = 1.f;

        if (position.y >= windowHeight - mHeight)
        {
            yDirection = -1.f;
        }
        else if (position.y <= 720 + mHeight)
        {
            yDirection = 1.f;
        }

        SetDirectionY(yDirection, GetSpeed());
    }
    else if(mCurrentPlayerTarget && mCurrentPlayerTarget->IsAlive())
    {
        GoToPosition(mCurrentPlayerTarget->GetPosition().x,mCurrentPlayerTarget->GetPosition().y, GetSpeed());
    }
}

void SuicideCar::OnCollision(LESprite* collidedWith)
{
    if (collidedWith->IsTag(-6))
    {
        std::cout << collidedWith->GetTag() << std::endl;
        Projectile* projecollider = dynamic_cast<Projectile*>(collidedWith);
        if (projecollider)
        {
            mLife -= projecollider->GetDamage();
            projecollider->Destroy();
            if (mLife <= 0)
            {
                
                Destroy();
            }
        }
    }
    if (collidedWith->IsTag(-11))
    {
        Projectile* projecollider = dynamic_cast<Projectile*>(collidedWith);

        if (projecollider) mLife -= projecollider->GetDamage();

        if (mLife <= 0)
        {
            Destroy();
        }
    }
}

void SuicideCar::OnInitialize()
{
}

void SuicideCar::CheckWindow()
{
    float constrainedY = std::clamp(this->GetPosition().y, 740.f - mHeight / 2, 1080.f - mHeight / 2);

    SetPosition(GetPosition().x, constrainedY);
}

int SuicideCar::GetDamage()
{
    return mDamage;
}

void SuicideCar::SetPlayerTarget(Player* target)
{
    mCurrentPlayerTarget = target;
}

float SuicideCar::GetSpeed()
{
    return mSpeed;
}

int SuicideCar::GetLife()
{
    return mLife;
}
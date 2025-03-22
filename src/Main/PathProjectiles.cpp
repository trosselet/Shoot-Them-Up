#include "pch.h"
#include "PathProjectiles.h"

#include "pch.h"
#include "PathProjectiles.h"
#include "Projectile.h"
#include"Boss.h"

void PathProjectiles::OnInitialize()
{
}

void PathProjectiles::OnUpdate()
{


}

void PathProjectiles::OnCollision(LESprite* collidedWith)
{
    if (collidedWith->IsTag(-6))
    {
        Projectile* projecollider = dynamic_cast<Projectile*>(collidedWith);

        if (projecollider)
        {
            /* projecollider->Destroy();*/
            mLife -= projecollider->GetDamage();

            if (mLife <= 0)
            {
                if (pBoss != nullptr)
                {


                    pBoss->RemovePathProjectiles(this);
                }


                Destroy();
            }

        }
    }

}

float PathProjectiles::GetSpeed()
{
    return mSpeed;
}

int PathProjectiles::GetDamage()
{
    return mDamage;
}

void PathProjectiles::SetDamage(int damage)
{
    mDamage = damage;
}
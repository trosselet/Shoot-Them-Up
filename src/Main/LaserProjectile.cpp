#include "pch.h"
#include "LaserProjectile.h"

int LaserProjectile::GetDamage()
{
    return mDamage;
}

void LaserProjectile::SetDamage(int damage)
{
    mDamage = damage;
}

void LaserProjectile::OnUpdate()
{
}

void LaserProjectile::OnCollision(LESprite* collidedWith)
{
}

void LaserProjectile::OnInitialize()
{
    SetTag(-10);
}

void LaserProjectile::CheckWindow()
{
}

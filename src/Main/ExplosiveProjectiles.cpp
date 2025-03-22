#include "pch.h"
#include "ExplosiveProjectiles.h"
#include <cmath>

void ExplosiveProjectiles::OnUpdate()
{
    //mElapsedTime += GetDeltaTime();

    //// V�rifier si le projectile doit exploser
    //if (mElapsedTime >= mExplosionTimer)
    //{
    //    Explode();
    //    Destroy(); // D�truire le projectile principal apr�s l'explosion
    //}

    mElapsedTime += GetDeltaTime();

    mSpeed += macceleration;
    // V�rifier si le projectile doit exploser
    if (mElapsedTime >= mExplosionTimer)
    {
        Explode();
        Destroy(); // D�truire le projectile principal apr�s l'explosion
    }
}

void ExplosiveProjectiles::OnCollision(LESprite* collidedWith)
{
}

void ExplosiveProjectiles::Explode()
{
    const Vector2<float> origin = GetPosition();

    for (int i = 0; i < mNumFragments; ++i)
    {
        // Calcule angle 
        float angle = (2 * 3.14f / mNumFragments) * i;

        // Calcul  direction fragment
        Vector2<float> direction(std::cos(angle), std::sin(angle));

        fragment = GetScene()->CreateEntity< ProjectileEnnemi>("../../res/Testing/Proj/1", this->GetAssetManager(), 9); // Exemple de cr�ation
        if (fragment)
        {
            fragment->SetPosition(origin.x, origin.y);
            fragment->SetDirection(direction.x, direction.y, mFragmentSpeed);
        }
    }
}

float ExplosiveProjectiles::GetSpeed()
{
    return mSpeed;
}
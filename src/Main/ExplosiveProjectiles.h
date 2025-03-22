#pragma once
#include "LE.h"
#include "ProjectileEnnemi.h"

class ExplosiveProjectiles : public LESprite
{
    float mExplosionTimer = 3.0f;
    float mElapsedTime = 0.0f;
    int mNumFragments = 20;
    float mFragmentSpeed = 300.f;
    float macceleration = 1;
    ProjectileEnnemi* fragment;

public:
    void OnUpdate() override;
    void OnCollision(LESprite* collidedWith) override;
    void Explode();
    float GetSpeed();

};

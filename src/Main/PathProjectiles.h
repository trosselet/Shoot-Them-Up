#pragma once
#pragma once
#include "LE.h"


class Boss;

class PathProjectiles : public LESprite
{

    int mDamage = 1;
    float mShootCooldown = 3.0f;
    float mShootCooldownTimer = 0.0f;
    int mLife = 3;
    Boss* pBoss;

public:
    void OnInitialize() override;
    void OnUpdate() override;
    void OnCollision(LESprite* collidedWith) override;
    float GetSpeed();
    int GetDamage();
    void SetDamage(int damage);

};
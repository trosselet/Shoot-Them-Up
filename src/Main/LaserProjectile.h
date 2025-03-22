#pragma once
#include "LE.h"

class LaserProjectile : public LESprite
{
    int mDamage = 10;

public:
    int GetDamage();
    void SetDamage(int damage);
    void OnUpdate() override;
    void OnCollision(LESprite* collidedWith) override;
    void OnInitialize() override;
    void CheckWindow();
};


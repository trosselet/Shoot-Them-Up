#pragma once
#include "LE.h"
#include "Ennemis.h"
#include "Projectile.h"
#include <iostream>

class SeekingProjectiles : public Projectile
{
  
    int mDamage;
    Ennemis* mCurrentTarget = nullptr; 
    std::vector<Ennemis*> mEnnemisList;

public:
    int GetDamage();
    void SetDamage(int damage);
    float GetSpeed();
    void OnUpdate() override;
    void OnCollision(LESprite* collidedWith) override;
    void OnInitialize() override;
    void CheckWindow();
    void SetEnnemisList(std::vector<Ennemis*>* ennemisList);
};


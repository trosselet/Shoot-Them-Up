#pragma once
#include"Ennemis.h"
#include "LE.h"
#include "SampleScene.h"
#include "Vector2.h"
#include "Player.h"
#include "Projectile.h"

class SampleScene;

class SuicideCar : public Ennemis
{
    int mLife = 2;
    float mCooldownSuicide = 2.0f;
    float mCooldownSuicideTimer;
    Player* mCurrentPlayerTarget = nullptr;
    SampleScene* mSampleScene;
    int mDamage = 10;

public:
    void OnUpdate() override;
    void OnCollision(LESprite* collidedWith) override;
    void OnInitialize() override;
    void CheckWindow();
    int GetDamage();
    void SetPlayerTarget(Player* target);
    float GetSpeed();
    int GetLife();
};
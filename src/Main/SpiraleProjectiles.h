#pragma once
#include "LE.h"
#include "Projectile.h"

class SpiraleProjectiles : public Projectile
{
    float mAngle = 0.f;                // Angle initial
    float mRadius = 100.f;              // Rayon initial
    float mAngleSpeed = 0.05f;          // Vitesse de rotation
    float mRadiusSpeed = 40.f;         // Vitesse d'expansion du rayon
    float mSpacingFactor = 0.05f;      // Facteur d'augmentation de l'espacement entre les projectiles
    float mElapsedTime = 0.f;          // Temps écoulé
    float mMaxDistance = 800.f;        // Distance maximale de la spirale
         

public:
    void OnInitialize() override;
    void OnUpdate() override;
    void OnCollision(LESprite* collidedWith) override;
    float GetSpeed();
};





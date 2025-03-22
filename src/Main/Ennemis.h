#pragma once
#include "LE.h"
#include "ProjectileEnnemi.h"
#include "Projectile.h"

class Scene;
class SampleScene;

class Ennemis : public LESprite
{
protected:

	int mLife = 5;
	ProjectileEnnemi* projectileEnnemis;
	float mShootCooldownEnnemisTimer;
	bool mIsAlive = true;
	bool mIsStunned = false;
	float mStunTimer = 0.f;
	SampleScene* mSampleScene;

	std::vector<Ennemis*>* myList = nullptr;

public:
	bool IsAlive() const;
	void OnUpdate() override;
	void OnCollision(LESprite* collidedWith) override;
	void OnInitialize() override;
	void CheckWindow();
	float GetSpeed();
	void Shoot();
	void SetList(std::vector<Ennemis*>* list) { myList = list; }
	void Stun(float duration);
	void IsStunned();
	void SetScene(SampleScene* scene) { mSampleScene = scene; }
};
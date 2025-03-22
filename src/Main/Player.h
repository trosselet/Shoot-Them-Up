#pragma once
#include "LE.h"
#include "Projectile.h"
#include "LaserProjectile.h"
#include "ProjectileEnnemi.h"
#include "Ennemis.h"
#include "SpriteAnimator.h"
#include "SuicideCar.h"
#include "SeekingProjectiles.h"

class Player : public LESprite
{
	SpriteAnimator* mpSpriteAnimator;

	LEInput* input;

	int mMaxLife = 5;
	int mCurrentLife = 5;
	int mMaxAmmo = 3;             
	int mCurrentAmmo = 3;         
	float mReloadTimer = 0.f;     
	float mReloadTime = 3.f;      
	bool mReloading = false;  
	float mParadeTimer = 0.f;
	float mParadeTime = 1.2f;

	float mShootCooldownTimer = 0.f;
	float mShootCooldownTime = 0.3f;
	float mLaserDamageTimer = 0.f;
	float mLaserDamageInterval = 0.5f;
	int mLaserDamageAmount = 5;
	bool mIsInLaserRange = false;
	bool isAlive = true;

	bool IsParadeActive = false;
	bool mTripleShotEnabled;
	bool mEPressed = false;
	SeekingProjectiles* pSeekingProjectiles;
	Projectile* pProjectile;
	SampleScene* mSampleScene;
	LESound* pSound;
	LERect* mParadeRect;
	std::vector<Ennemis*>* myList = nullptr;

public:


	void OnUpdate() override;
	void OnCollision(LESprite* collidedWith) override;
    void OnInitialize() override;
	void CheckWindow();
	float GetSpeed();
	void SetLife(int life);
	void SetMaxLife(int MaxLife);
	int GetLife() { return mCurrentLife; }
	float GetReloadTimer();
	void SetReloadTimer(float reloadtimer);
	float GetReloadTime();
	void SetReloadTime(float reloadtimer);
	void FireSeekingProjectiles();
	void UpdateReload();
	int GetCurrentAmmo() const { return mCurrentAmmo; }
	bool IsReloading() const { return mReloading; }
	float GetReloadProgress() const { return mReloadTimer / mReloadTime; }
	bool& IsAlive() { return isAlive; }
	void SetTripleShotEnabled(bool enabled);
	bool GetTripleShotEnabled();
	void FireTripleShot();
	bool CheckParadeCollision(ProjectileEnnemi* projectile);
	void HandleParadeSuccess(ProjectileEnnemi* projectile);
	void SetList(std::vector<Ennemis*>* list) { myList = list; }
	void SetScene(SampleScene* scene) { mSampleScene = scene; }
	void SetInput(LEInput* _input) { input = _input; }
};


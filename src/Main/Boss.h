#pragma once
#pragma once
#include "Ennemis.h"
#include "StateMachine.h"
#include "ExplosiveProjectiles.h"
#include "SpiraleProjectiles.h"
#include "PathProjectiles.h"
#include "LE.h"
#include "ProjectileEnnemi.h"
#include "Vector2.h"


class SampleScene;

class Boss : public Ennemis
{

	StateMachine<Boss> mStateMachine;

	enum State
	{
		PHASE1,
		PHASE2,

		Count
	};

	int mLifeMax = 4;
	int mCurrentLife = 4;
	float mShootTime = 6.0f;
	float mShootTimer = 0.f;
	float mEclipseTimer = 0.f;
	float mEclipseTime = 1.0f;
	float mPathTimer = 0.f;
	float mPathTime = 1.0f;
	ExplosiveProjectiles* pExplosive;
	SpiraleProjectiles* pSpirale;
	PathProjectiles* pPath;
	ProjectileEnnemi* pProjectile;
	SampleScene* mSampleScene;

	float mFireshootTimer = 0.f;
	float mFireShootTime = 1.0f;
	float mPauseTimer = 0.0f;
	float mCornerTimer = 0.0f;
	float mCornerTime = 6.0f;
	float mPauseDuration = 7.f;
	bool mIsTracing = true;
	bool mIsRectangleMoving = false;
	std::list<PathProjectiles*> mRectangleProjectiles;
	float mRectangleSpeed = 250.0f;
	float mRectangleWidth = 200.f;
	float mRectangleHeight = 300.f;

public:

	Boss();
	bool IsAlive() const;
	void OnUpdate() override;
	void OnCollision(LESprite* collidedWith) override;
	void OnInitialize() override;
	void CheckWindow();
	float GetSpeed();
	int GetVie();
	void SetVieMax(int Vie);
	void TraceRectangle();
	void MoveRectangle();
	void CreateEntityPath();
	void RemovePathProjectiles(PathProjectiles* pathProjectiles);
	void FireTriplePacket();
	void SetScene(SampleScene* scene) { mSampleScene = scene; }
	
	friend class  BossAction_Phase1;
	friend class  BossAction_Phase2;
	friend class  PathProjectiles;
};


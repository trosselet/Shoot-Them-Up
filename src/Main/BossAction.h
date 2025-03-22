#pragma once
#pragma once
#include "Action.h"
#include "Boss.h"
#include "ExplosiveProjectiles.h"
#include "Vector2.h"
#include "SpiraleProjectiles.h"


class BossAction_Phase1 : public Action<Boss>
{
	float mShootTimer = 0.f;
	float mShootTime = 2.0f;
	float mEclipseTimer = 0.f;
	float mEclipseTime = 1.0f;
	ExplosiveProjectiles* pExplosive;
	SpiraleProjectiles* pSpirale;

public:
	void Start(Boss* pBoss) override;
	void Update(Boss* pBoss) override;
	void End(Boss* pBoss) override;
};

class BossAction_Phase2 : public Action<Boss>
{
	float mShootTimer = 0.f;
	float mShootTime = 2.0f;
	float mEclipseTimer = 0.f;
	float mEclipseTime = 1.0f;
	float mFireshootTimer = 0.f;
	float mFireShootTime = 3.0f;
	ExplosiveProjectiles* pExplosive;
	SpiraleProjectiles* pSpirale;

public:
	void Start(Boss* pBoss) override;
	void Update(Boss* pBoss) override;
	void End(Boss* pBoss) override;
};
#include "pch.h"
#include "BossAction.h"
#include "pch.h"
#include "BossAction.h"
#include "Boss.h"

void BossAction_Phase1::Start(Boss* pBoss)
{
}

void BossAction_Phase1::Update(Boss* pBoss)
{

	float deltaTime = pBoss->GetDeltaTime();
	float windowHeight = pBoss->GetScene()->GetWindowHeight();
	float bossHeight = 100;
	int attack = rand() % 100;

	if (pBoss->GetPosition().y <= 0 && pBoss->mDirection.y < 0)
	{
		pBoss->SetDirection(0.0f, 1.0f, 400.f);
	}
	else if (pBoss->GetPosition().y + bossHeight >= windowHeight && pBoss->mDirection.y > 0)
	{
		pBoss->SetDirection(0.0f, -1.0f, 400.f);
	}


	Vector2<float> position = pBoss->GetPosition();
	position.y += pBoss->mDirection.y * 400.f * deltaTime;
	pBoss->SetPosition(position.x, position.y);

	if (attack < 40) // 40% de chances : attaque explosive
	{
		mShootTimer += deltaTime;
		if (mShootTimer >= mShootTime)
		{
			pExplosive = GameManager::Get()->GetScene()->CreateEntity<ExplosiveProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
			if (pExplosive)
			{
				pExplosive->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y);
				pExplosive->SetSpeed(200.f);
				pExplosive->SetDirection(-1.0f, 0.f, pExplosive->GetSpeed());
			}
			mShootTimer = 0.0f;
		}
	}
	else if (attack < 70) // 30% de chances : spirale
	{
		mEclipseTimer += deltaTime;
		if (mEclipseTimer >= mEclipseTime)
		{
			pSpirale = GameManager::Get()->GetScene()->CreateEntity<SpiraleProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
			if (pSpirale)
			{
				pSpirale->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y);
				pSpirale->SetSpeed(0.f);
			}
			mEclipseTimer = 0.0f;
		}
	}
	else if (attack < 90) // 20% de chances : tir spécial
	{


		pBoss->FireTriplePacket();


	}
	else // 10% de chances : attaque combinée
	{


		pBoss->FireTriplePacket();


		mEclipseTimer += deltaTime;
		if (mEclipseTimer >= mEclipseTime)
		{
			pSpirale = GameManager::Get()->GetScene()->CreateEntity<SpiraleProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
			if (pSpirale)
			{
				pSpirale->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y);
				pSpirale->SetSpeed(0.f);
			}
			mEclipseTimer = 0.0f;
		}
	}

}

void BossAction_Phase1::End(Boss* pBoss)
{
}

void BossAction_Phase2::Start(Boss* pBoss)
{


}

void BossAction_Phase2::Update(Boss* pBoss)
{
	if (pBoss->mIsTracing)
	{
		pBoss->TraceRectangle(); // Le boss trace un rectangle avec des projectiles
	}
	if (pBoss->mIsRectangleMoving)
	{
		pBoss->MoveRectangle(); // Le rectangle de projectiles se déplace sur X
	}

	int attack = rand() % 100;
	float deltaTime = pBoss->GetDeltaTime();
	if (attack < 40) // 40% de chances : attaque explosive
	{
		mShootTimer += deltaTime;
		if (mShootTimer >= mShootTime)
		{
			pExplosive = GameManager::Get()->GetScene()->CreateEntity<ExplosiveProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
			if (pExplosive)
			{
				pExplosive->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y);
				pExplosive->SetSpeed(200.f);
				pExplosive->SetDirection(-1.0f, 0.f, pExplosive->GetSpeed());
			}
			mShootTimer = 0.0f;
		}
	}
	else if (attack < 70) // 30% de chances : spirale
	{
		mEclipseTimer += deltaTime;
		if (mEclipseTimer >= mEclipseTime)
		{
			pSpirale = GameManager::Get()->GetScene()->CreateEntity<SpiraleProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
			if (pSpirale)
			{
				pSpirale->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y);
				pSpirale->SetSpeed(0.f);
			}
			mEclipseTimer = 0.0f;
		}
	}
	else if (attack < 90) // 20% de chances : tir spécial
	{


		pBoss->FireTriplePacket();


	}
	else // 10% de chances : attaque combinée
	{


		pBoss->FireTriplePacket();


		mEclipseTimer += deltaTime;
		if (mEclipseTimer >= mEclipseTime)
		{
			pSpirale = GameManager::Get()->GetScene()->CreateEntity<SpiraleProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
			if (pSpirale)
			{
				pSpirale->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y);
				pSpirale->SetSpeed(0.f);
			}
			mEclipseTimer = 0.0f;
		}
	}

}

void BossAction_Phase2::End(Boss* pBoss)
{
}
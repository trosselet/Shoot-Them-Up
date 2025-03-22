#include "pch.h"
#include "Boss.h"
#include "pch.h"
#include "Boss.h"
#include"ExplosiveProjectiles.h"
#include <iostream>
#include "SampleScene.h"
#include "BossCondition.h"
#include "BossAction.h"

Boss::Boss() : mStateMachine(this, State::Count)
{
	//PHASE 1
	{

		Behaviour<Boss>* pPhase1 = mStateMachine.CreateBehaviour(State::PHASE1);
		pPhase1->AddAction(new BossAction_Phase1());


		//->PHASE 2
		{
			auto transition = pPhase1->CreateTransition(State::PHASE2);

			auto condition = transition->AddCondition<BossCondition_HalfLife>();

		}
	}
	
	mStateMachine.SetState(State::PHASE1);

}

bool Boss::IsAlive() const
{
	return false;
}

void Boss::OnUpdate()
{
	////boss Action update après
	//mShootTimer += GetDeltaTime();

	//if (mShootTimer >= mShootTime)
	//{
	//    // Créer le projectile explosif
	//    pExplosive = CreateEntity<ExplosiveProjectiles>(10, sf::Color::Red);
	   //      
	//        pExplosive->SetPosition(GetPosition().x, GetPosition().y);
	//        pExplosive->SetSpeed(200.f);
	//        pExplosive->SetDirection(-1.0f, 0.f, pExplosive->GetSpeed());
	//    

	//        mShootTimer = 0.0f;
	//}

	//mEclipseTimer += GetDeltaTime();
	//if (mEclipseTimer >= mEclipseTime) 
	//{
	//      pSpirale = CreateEntity<SpiraleProjectiles>(20, sf::Color::Cyan); 
	//    if ( pSpirale) 
	//    {  
	//        pSpirale->SetPosition(GetPosition().x, GetPosition().y); 
	//       pSpirale->SetSpeed(0.f);
	//    }
	//    mEclipseTimer = 0.0f;
	//}
	// Vérification de l'arrivée à la cible

   /*mShootTimer += GetDeltaTime();

	if (mShootTimer >= mShootTime)
	{

		FireTriplePacket();

			mShootTimer = 0.0f;
	}*/

	if (mCurrentLife <= 0)
	{
		Destroy();
	}

	if (mCurrentLife > 0)
	{
		mStateMachine.Update();
	}
	

	//if (mIsTracing)
	//{
	//	TraceRectangle(); // Le boss trace un rectangle avec des projectiles
	//}
	//if (mIsRectangleMoving)
	//{
	//	MoveRectangle(); // Le rectangle de projectiles se déplace sur X
	//}

}


void Boss::OnCollision(LESprite* collidedWith)
{
	if (collidedWith->IsTag(-6))
	{
		Projectile* projecollider = dynamic_cast<Projectile*>(collidedWith);

		if (projecollider)
		{
			mCurrentLife -= projecollider->GetDamage();

			if (projecollider->WasParried())
			{

				Stun(3.0f);
				std::cout << "Stun called with duration: 3.0f" << std::endl;
				mCurrentLife -= projecollider->GetDamage();
			}
			projecollider->Destroy();
		}
	}

}

void Boss::OnInitialize()
{
	SetDirection(0.f, 1.f, 400.f);


}

void Boss::CheckWindow()
{
}

float Boss::GetSpeed()
{
	return mSpeed;
}

int Boss::GetVie()
{
	return mCurrentLife;
}

void Boss::SetVieMax(int VieMax)
{
	mLifeMax = VieMax;
}

void Boss::TraceRectangle()
{
	float windowX = 1300;
	float windowY = GetScene()->GetWindowHeight() / 2;

	float topBoundary = windowY - mRectangleHeight;
	float bottomBoundary = windowY + mRectangleHeight;
	float leftBoundary = windowX - mRectangleWidth;
	float rightBoundary = windowX + mRectangleWidth;



	if (GetPosition().y <= topBoundary && mDirection.y < 0)
	{
		SetDirection(1.0f, 0.0f, 500.f); // Passer à la droite
		mCornerTimer += 1.0f;
	}
	else if (GetPosition().x >= rightBoundary && mDirection.x > 0)
	{
		SetDirection(0.0f, 1.0f, 500.f); // Passer au bas
		mCornerTimer += 1.0f;
	}
	else if (GetPosition().y >= bottomBoundary && mDirection.y > 0)
	{
		SetDirection(-1.0f, 0.0f, 500.f); // Passer à la gauche
		mCornerTimer += 1.0f;
	}
	else if (GetPosition().x <= leftBoundary && mDirection.x < 0)
	{
		SetDirection(0.0f, -1.0f, 500.f); // Retourner en haut
		mCornerTimer += 1.0f;
	}
	if (mCornerTimer >= mCornerTime)
	{
		// Condition pour arrêter le traçage une fois le rectangle terminé
		mIsTracing = false;
		mIsRectangleMoving = true;
		SetDirection(0.0f, 0.0f, 0.0f);
		mCornerTimer = 0.0f;
	}
	if (mIsTracing)
	{
		CreateEntityPath();
	}
}

void Boss::MoveRectangle()
{
	for (auto* projectile : mRectangleProjectiles)
	{
		if (projectile)
		{
			Vector2<float> position = projectile->GetPosition();
			position.x += -mRectangleSpeed * GetDeltaTime();
			projectile->SetPosition(position.x, position.y);
		}
	}

	mPauseTimer += GetDeltaTime();
	if (mPauseTimer >= mPauseDuration)
	{
		mPauseTimer = 0.0f;
		mIsRectangleMoving = false;
		mIsTracing = true;
		SetDirection(-1.0f, 1.f, GetSpeed());
	}
}

void Boss::CreateEntityPath()
{
	pPath = GetScene()->CreateEntity<PathProjectiles>("../../res/Testing/Proj/1", GameManager::Get()->GetAssetManager(), 9);
	pPath->SetPosition(GetPosition().x, GetPosition().y);
	pPath->SetSpeed(150.f);
	mRectangleProjectiles.push_back(pPath);
}

void Boss::RemovePathProjectiles(PathProjectiles* pathProjectiles)
{
	if (pathProjectiles == nullptr) return;

	mRectangleProjectiles.erase(std::remove(mRectangleProjectiles.begin(), mRectangleProjectiles.end(), pathProjectiles), mRectangleProjectiles.end());

	/*
	auto it = std::find(mRectangleProjectiles.begin(), mRectangleProjectiles.end(), pathProjectiles);
	if (it != mRectangleProjectiles.end())
	{
		mRectangleProjectiles.erase(it);
	}*/
}

void Boss::FireTriplePacket()
{
	mFireshootTimer += GetDeltaTime();

	if (mFireshootTimer >= mFireShootTime)
	{

		float speed = 150.f;
		// Direction des trois paquets
		//std::vector<sf::Vector2f> directions = {
		//	{-1.0f, 0.0f}, // Vers la gauche
		//	{0.0f, -1.0f}, //  Vers le bas (ou centre selon l'orientation)
		//	{1.0f, 0.0f}   //  Vers la droite
		//};
		std::vector<float> angles = { -30.0f, 0.0f, 30.0f };


		for (int i = 0; i < 3; ++i) {

			for (int j = -1; j <= 1; ++j) {
				float angleInRadians = angles[i] * (3.14 / 180.0f);
				float directionX = cos(angleInRadians);
				float directionY = sin(angleInRadians);

				pProjectile = GetScene()->CreateEntity<ProjectileEnnemi>("../../res/Testing/Proj/Tir0001", this->GetAssetManager(), 9);


				Vector2<float> newPos = GetPosition();;
				newPos.x += j * 50.f;
				newPos.y += j * 50.f;

				pProjectile->SetPosition(newPos.x, newPos.y);

				pProjectile->SetDirection(-directionX, directionY, speed);
				pProjectile->SetTag(-7);
				mSampleScene->AddProjectile(pProjectile);
			}
		}
		mFireshootTimer = 0.f;
	}

}


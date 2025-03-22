#include "pch.h"
#include "Player.h"
#include <iostream>

void Player::OnUpdate()
{
	CheckWindow();

	SetDirection(0.f,0.f,0.f);

	if (mCurrentLife <= 0)
	{
		isAlive = false;
		Destroy();

	}
	
    UpdateReload();

	mParadeTimer += GetDeltaTime();

	mpSpriteAnimator->Update(GameManager::Get()->GetDeltaTime());

	if (mCurrentLife > 0)
	{
		if (input->GetKeyState("Z") == KeyState::STAY || input->GetKeyState("Z") == KeyState::DOWN)
		{
			SetDirectionY(-1.f, GetSpeed());
		}
		if (input->GetKeyState("S") == KeyState::STAY || input->GetKeyState("S") == KeyState::DOWN)
		{
			SetDirectionY(1.f, GetSpeed());
		}
		if (input->GetKeyState("Q") == KeyState::STAY || input->GetKeyState("Q") == KeyState::DOWN)
		{
			SetDirectionX(-1.f, GetSpeed());
		}
		if (input->GetKeyState("D") == KeyState::STAY || input->GetKeyState("D") == KeyState::DOWN)
		{
			SetDirectionX(1.f,GetSpeed());
		}

		/*if (input->GetKeyState("E") == KeyState::DOWN && !myList->empty())
		{
			if (!mEPressed)
			{
				mEPressed = true;

				if (IsReloading())
				{
					std::cout << "Cannot fire! Reloading..." << std::endl;
				}
				else if (GetCurrentAmmo() > 0)
				{
					SeekingProjectiles* projectile = mSampleScene->CreateEntity<SeekingProjectiles>("../../res/Testing/Proj/Tir0007", this->GetAssetManager(), 9);

					if (!projectile)
					{
						std::cerr << "Failed to create seeking projectile!" << std::endl;
						return;
					}

					projectile->SetSpeed(1000.f);
					projectile->SetPosition(GetPosition().x, GetPosition().y);
					projectile->SetEnnemisList(myList);
					projectile->SetTag(-6);

					FireSeekingProjectiles();
				}
				else
				{
					std::cout << "No ammo left! Reloading..." << std::endl;
				}
			}
		}
		else
		{
			mEPressed = false;
		}*/
		if (mCurrentLife > 0)
		{
			mShootCooldownTimer += GameManager::Get()->GetDeltaTime();
			if (mShootCooldownTimer >= 1)
			{
				if (GetTripleShotEnabled())
				{
					FireTripleShot();
					mShootCooldownTimer = 0.f;
				}
				else
				{
					pProjectile = GetScene()->CreateEntity<Projectile>("../../res/Testing/Proj/Tir0001", this->GetAssetManager(), 9);
					pProjectile->SetPosition(GetPosition().x, GetPosition().y);
					pProjectile->SetDirection(1.f, 0.f, pProjectile->GetSpeed());
					pProjectile->SetTag(-6);
					pSound->Play();
					mShootCooldownTimer = 0.f;
				}
			}
		}

		if (input->GetKeyState("Space") == KeyState::DOWN)
		{

			if (mParadeTimer >= mParadeTime)
			{
				if (!IsParadeActive)
				{
					IsParadeActive = true;

					for (auto* projectile : mSampleScene->GetProjectiles())
					{
						if (CheckParadeCollision(projectile))
						{
							projectile->SetParried(true);
							projectile->SetTag(-6);
							HandleParadeSuccess(projectile);
						}
					}
				}
				mParadeTimer = 0.0f;
			}
		}
		else
		{
			IsParadeActive = false;
		}
	}
}

void Player::OnCollision(LESprite* collidedWith)
{	
	if (collidedWith->IsTag(-7))
	{
		ProjectileEnnemi* projecollider = dynamic_cast<ProjectileEnnemi*>(collidedWith);

		if (projecollider)
		{
			mCurrentLife -= projecollider->GetDamage();
			projecollider->Destroy();

			return;
		}
	}

	if (collidedWith->IsTag(2) || collidedWith->IsTag(3) || collidedWith->IsTag(5))
	{
		Ennemis* ennemie = dynamic_cast<Ennemis*>(collidedWith);
		std::cout << "Player encountered an ennemy!" << std::endl;
		if (ennemie)
		{
			mCurrentLife -= 1;
			ennemie->Destroy();
			if (mCurrentLife <= 0)
			{
				isAlive = false;
				Destroy();

			}
		}
	}

	if (collidedWith->IsTag(3))
	{
		SuicideCar* SuicideColl = dynamic_cast<SuicideCar*>(collidedWith);
		std::cout << "Player encountered an ennemy!" << std::endl;
		if (SuicideColl)
		{
			mCurrentLife -= 2;
		}
		SuicideColl->Destroy();

		if (mCurrentLife <= 0)
		{
			Destroy();
		}
	}

	if (collidedWith->IsTag(-10))
	{
		LaserProjectile* laserProjectile = dynamic_cast<LaserProjectile*>(collidedWith);

		if (laserProjectile)
		{

			if (laserProjectile)
			{

				if (!mIsInLaserRange) {
					mIsInLaserRange = true;
					mLaserDamageTimer = 0.f;
					std::cout << "Player entered laser range!" << std::endl;
				}


				if (mIsInLaserRange) {
					mLaserDamageTimer += GetDeltaTime();


					if (mLaserDamageTimer >= mLaserDamageInterval) {
						mLaserDamageTimer = 0.f;
						mCurrentLife -= mLaserDamageAmount;
						std::cout << "Player is taking laser damage!" << std::endl;

						if (mCurrentLife <= 0)
						{
							Destroy();
						}

					}
				}
			}
		}
	}
	else
	{
		if (mIsInLaserRange) {
			mIsInLaserRange = false;
			mLaserDamageTimer = 0.f;
			std::cout << "Player left laser range!" << std::endl;
		}
	}
	if (collidedWith->IsTag(3))
	{
		SuicideCar* SuicideColl = dynamic_cast<SuicideCar*>(collidedWith);

		if (SuicideColl) mCurrentLife = SuicideColl->GetDamage();
		SuicideColl->Destroy();

		if (mCurrentLife <= 0)
		{

			Destroy();

		}
	}


	if (collidedWith->IsTag(-2000))
	{
		return;
	}
}

void Player::OnInitialize()
{
	mpSpriteAnimator = new SpriteAnimator(this);

	std::vector<const char*> mWalkFrames =
	{
		"../../res/Testing/voiture",
		"../../res/Testing/voiture2",
		"../../res/Testing/voiture3",
		"../../res/Testing/voiture4",
		"../../res/Testing/voiture5",
		"../../res/Testing/voiture6"
	};

	mpSpriteAnimator->CreateAnimation("Walk", mWalkFrames, 0.1f);
	mpSpriteAnimator->SetAnimation("Walk");
	pSound = GetScene()->CreateSound("../../res/Testing/Bruit.mp3", GameManager::Get()->GetAudioManager(), 100);
}

void Player::CheckWindow()
{
	float constrainedX = std::clamp(this->GetPosition(0.5, 0.5).x, (float)(mWidth / 2), 1920.f - mWidth / 2);
	float constrainedY = std::clamp(this->GetPosition(0.5, 0.5).y, 740.f - mHeight / 2, 1080.f - mHeight / 2);

	SetPosition(constrainedX, constrainedY);
}

float Player::GetSpeed()
{
	return mSpeed;
}

void Player::SetLife(int life)
{
	mCurrentLife = life;
}

void Player::SetMaxLife(int MaxLife)
{
	mMaxLife = MaxLife;
}

float Player::GetReloadTimer()
{
	return mReloadTimer;
}

void Player::SetReloadTimer(float reloadtimer)
{
	mReloadTimer = reloadtimer;
}

float Player::GetReloadTime()
{
	return mReloadTime;
}

void Player::SetReloadTime(float reloadtimer)
{
	mReloadTime = reloadtimer;
}

void Player::FireSeekingProjectiles()
{
	if (mReloading)
	{
		std::cout << "Reloading in progress! Wait..." << std::endl;
		return;
	}

	if (mCurrentAmmo > 0)
	{
		--mCurrentAmmo;
		std::cout << "Missile fired! Ammo remaining: " << mCurrentAmmo << std::endl;

		
		if (mCurrentAmmo == 0)
		{
			mReloading = true;
			mReloadTimer = 0.f; 
		}
	}
	else
	{
		std::cout << "No ammo left! Reload required." << std::endl;
	}
}

void Player::UpdateReload()
{
	if (mReloading)
	{
		mReloadTimer += GetDeltaTime(); 

		if (mReloadTimer >= mReloadTime)
		{
			mCurrentAmmo = mMaxAmmo; 
			mReloading = false;      
			std::cout << "Reload complete! Ammo refilled." << std::endl;
		}
	}
}

void Player::SetTripleShotEnabled(bool enabled)
{
	mTripleShotEnabled = enabled;
}

bool Player::GetTripleShotEnabled()
{
	return mTripleShotEnabled;
}

void Player::FireTripleShot()
{
	
    std::vector<Vector2<float>> directions = {
	{1.0f, 0.0f},  // Centre
	{0.866f, -0.5f}, // Gauche 
	{0.866f, 0.5f},  // Droite 
	{0.707f, -0.707f}, // Plus à gauche 
	{0.707f, 0.707f}   // Plus à droite 
	};

	for (int i = 0; i < 5; ++i) {
		Projectile* pProjectile = GetScene()->CreateEntity<Projectile>("../../res/Testing/Proj/Tir0001", this->GetAssetManager(), 9);
		pProjectile->SetTag(-6);

		Vector2<float> newPos = GetPosition();;
		if (i == 1 || i == 3) {
			newPos.x -= 10.0f;
		}
		else if (i == 2 || i == 4) {
			newPos.x += 10.0f;
		}

		// Appliquer la position et la direction du projectile
		pProjectile->SetPosition(newPos.x, newPos.y);
		pProjectile->SetDirection(directions[i].x, directions[i].y, 200.f);
	}
}

bool Player::CheckParadeCollision(ProjectileEnnemi* projectile)
{
	Vector2<float> position = GetPosition();
	float width = GetTexture()->GetWidth() + 100;
	float height = GetTexture()->GetHeight();

	if (!projectile)
		return false;

	auto otherPosition = projectile->GetPosition();
	float otherWidth = projectile->GetTexture()->GetWidth();
	float otherHeight = projectile->GetTexture()->GetHeight();

	return (position.x < otherPosition.x + otherWidth &&
		position.x + width > otherPosition.x &&
		position.y < otherPosition.y + otherHeight &&
		position.y + height > otherPosition.y
		);
	
}

void Player::HandleParadeSuccess(ProjectileEnnemi* projectile)
{
	Vector2<float> playerPosition = GetPosition();
	Vector2<float> projectilePosition = projectile->GetPosition();
	Vector2<float> direction = projectilePosition - playerPosition;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0.0f)
	{
		direction.x /= length;
		direction.y /= length;
	}

	projectile->SetDirection(direction.x, direction.y, projectile->GetSpeed());
}

#pragma once

#include "Scene.h"

//class SFMLEntity;
//class DummyEntity;

#include "LE.h"
#include <iostream>

class Player;
class Ennemis;
class Projectile;
class SeekingProjectiles;
class SuicideCar;
class LaserCar;
class Boss;
class ProjectileEnnemi;

class SampleScene : public Scene
{
	LEInput* input;

	Player* pPlayer;
	Ennemis* pEnnemis;
	Projectile* pProjectile;
	SeekingProjectiles* pSeekingProjectiles;
	SuicideCar* pSuicideCar;
	LaserCar* pLaserCar;
	Boss* pBoss;
	LEMusic* pMusic;
	LESound* pSound;

	LERect* pRect;

	std::vector<Ennemis*> ennemis;
	std::vector<LESprite*> entities;
	std::vector<ProjectileEnnemi*> mProjectiles;

	bool mSpacePressed = false;

	char a;
	const std::string lien = "../../res/Testing/Level.txt";
	std::string ligne;

	bool mIsFirstInitialize = true;


public:
	void OnInitialize() override;
	void OnEvent() override;
	void OnUpdate() override;
	void UpdateEnnemisList();
	void DestroyEntities();
	
	void AddProjectile(ProjectileEnnemi* projectile);
	void RemoveProjectile(ProjectileEnnemi* projectile);
	const std::vector<ProjectileEnnemi*>& GetProjectiles();
};



#include "pch.h"
#include "SampleScene.h"
#include "LE.h"
#include "Player.h"
#include "Projectile.h"
#include "SeekingProjectiles.h"
#include "SuicideCar.h"
#include "LaserCar.h"
#include "Ennemis.h"
#include "GameManager.h"

#include <sstream>
#include <fstream>
#include "ProjectileEnnemi.h"
#include "Boss.h"

void SampleScene::OnInitialize()
{
	if (!mIsFirstInitialize) {
		DestroyEntities();
	}
	else
	{
		input = new LEInput();
	}
	

	if (!pPlayer)
	{
		pPlayer = CreateEntity<Player>(("../../res/Testing/voiture"), this->GetAssetManager(), 7);
		pPlayer->SetPosition(400, 800);
		pPlayer->SetInitSpeed(500.f);
		pPlayer->SetTag(1);
		pPlayer->SetScene(this);
		pPlayer->SetInput(input);
		entities.push_back(pPlayer);
	}

	std::ifstream monFlux(lien);

	if (monFlux)
	{
		std::cout << "fichier ouvert" << std::endl;
		std::string ligne;
		int y = 0;

		while (std::getline(monFlux, ligne))
		{
			for (size_t x = 0; x < ligne.length(); ++x)
			{
				char c = ligne[x];

				if (c == '1')
				{
					pEnnemis = CreateEntity<Ennemis>(("../../res/Testing/Ennemies/Ennemy1"), this->GetAssetManager(), 7);
					pEnnemis->SetPosition(x * 50.f, y * 50.f);
					pEnnemis->SetSpeed(100.f);
					pEnnemis->SetTag(2);
					pEnnemis->SetScene(this);
					ennemis.push_back(pEnnemis);
					pEnnemis->SetList(&ennemis);
					entities.push_back(pEnnemis);
					std::cout << "Un ennemi spawn en (" << x * 50.f << ", " << y * 50.f << ")" << std::endl;
				}
				else if (c == '2')
				{
					pSuicideCar = CreateEntity<SuicideCar>(("../../res/Testing/Ennemies/Ennemy2"), this->GetAssetManager(), 7);
					pSuicideCar->SetPosition(x * 50.f, y * 50.f);
					pSuicideCar->SetSpeed(600.f);
					pSuicideCar->SetPlayerTarget(pPlayer);
					pSuicideCar->SetTag(3);
					ennemis.push_back(pSuicideCar);
					pSuicideCar->SetScene(this);
					pSuicideCar->SetList(&ennemis);
					entities.push_back(pSuicideCar);
					std::cout << "Une suicide car spawn en (" << x * 50.f << ", " << y * 50.f << ")" << std::endl;
				}
				else if (c == '3')
				{
					pLaserCar = CreateEntity<LaserCar>(("../../res/Testing/Ennemies/Ennemy3"), this->GetAssetManager(), 7);
					pLaserCar->SetTag(5);
					ennemis.push_back(pLaserCar);
					pLaserCar->SetList(&ennemis);
					pLaserCar->SetScene(this);
					entities.push_back(pLaserCar);
					std::cout << "Un laser car spawn en (" << x * 50.f << ", " << y * 50.f << ")" << std::endl;
				}
				else if (c == '4')
				{
					pBoss = CreateEntity<Boss>(("../../res/Testing/Ennemies/Boss"), this->GetAssetManager(), 7);
					pBoss->SetPosition(x * 50.f, y * 50.f);
					pBoss->SetScene(this);
					ennemis.push_back(pBoss);

					std::cout << "Un laser car spawn en (" << x * 50.f << ", " << y * 50.f << ")" << std::endl;
				}
				else if (c == '-')
				{

				}
			}
			y++;
		}
	}
	else
	{
		std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
	}	

	
	
	if (mIsFirstInitialize)
	{
		GameManager::Get()->AddParallaxBackground(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/Background/ciel"), 0, 80, 0);
		GameManager::Get()->AddParallaxBackground(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/Background/colline"), 1, 90, 540);
		GameManager::Get()->AddParallaxBackground(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/Background/bg2"), 2, 130, 360);
		GameManager::Get()->AddParallaxBackground(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/Background/bg1"), 3, 220, 360);
		GameManager::Get()->AddParallaxBackground(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/Background/barrieres"), 4, 220, 640);
		GameManager::Get()->AddParallaxBackground(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/Background/route"), 5, 480, 720);
	

		GameManager::Get()->AddUIElement(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/UI/Pause"), UIState::Pause);
		GameManager::Get()->AddUIElement(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/UI/Victoire"), UIState::Win);
		GameManager::Get()->AddUIElement(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/UI/Defaite"), UIState::Loose);
		GameManager::Get()->AddUIElement(GameManager::Get()->GetAssetManagerT()->GetTexture("../../res/Testing/UI/Menu"), UIState::Menu);

		pMusic = CreateMusic("../../res/Testing/Ameno.mp3", GameManager::Get()->GetAudioManager(), 100);
		pMusic->Play();

		mIsFirstInitialize = true;

	}

	
	/*pRect = CreateRect(440, 151);
	pRect->SetColor(255, 0, 0);*/

}

void SampleScene::OnEvent()
{
}

void SampleScene::OnUpdate()
{

	input->Update();

	std::cout << ennemis.size() << std::endl;

	if (GameManager::Get()->GetUICurrentState() == UIState::Menu)
	{
		if (input->GetKeyState("Enter") == KeyState::DOWN)
		{
			GameManager::Get()->SetUIState(UIState::Game);
		}
	}
	else if (GameManager::Get()->GetUICurrentState() == UIState::Win)
	{
		if (input->GetKeyState("Enter") == KeyState::DOWN)
		{
			GameManager::Get()->SetUIState(UIState::Menu);
		}
	}
	else if (GameManager::Get()->GetUICurrentState() == UIState::Loose)
	{
		if (input->GetKeyState("Enter") == KeyState::DOWN)
		{
			GameManager::Get()->SetUIState(UIState::Menu);
		}
	}
	else if (GameManager::Get()->GetUICurrentState() == UIState::Pause)
	{
		if (input->GetKeyState("P") == KeyState::DOWN)
		{
			GameManager::Get()->SetUIState(UIState::Game);
		}
	}
	else if (GameManager::Get()->GetUICurrentState() == UIState::Game)
	{
		UpdateEnnemisList();

		if (pPlayer->GetLife() > 0)
		{
			std::cout << "Alive" << std::endl;

			if (input->GetKeyState("P") == KeyState::DOWN)
			{
				GameManager::Get()->SetUIState(UIState::Pause);
			}
			if (ennemis.empty())
			{
				GameManager::Get()->SetUIState(UIState::Win);
			}
		}
		else
		{
			GameManager::Get()->SetUIState(UIState::Loose);
		}
	}
}

void SampleScene::UpdateEnnemisList()
{
	ennemis.erase(
		std::remove_if(ennemis.begin(), ennemis.end(),
			[](Ennemis* ennemi) { return ennemi == nullptr || !ennemi->IsAlive(); }),
		ennemis.end());

	mProjectiles.erase(
		std::remove_if(mProjectiles.begin(), mProjectiles.end(),
			[](ProjectileEnnemi* ennemi) { return ennemi == nullptr || !ennemi->ToDestroy(); }),
		mProjectiles.end());

	pPlayer->SetList(&ennemis);
}

void SampleScene::DestroyEntities()
{
	for (auto entity : entities)
	{
			
		if (entity != nullptr)
		{
			entity->Destroy();
			entities.erase(entities.begin());
		}
	}
	entities.clear();
	ennemis.clear();
}

void SampleScene::AddProjectile(ProjectileEnnemi* projectile)
{
	mProjectiles.push_back(projectile);
}

void SampleScene::RemoveProjectile(ProjectileEnnemi* projectile)
{
	mProjectiles.erase(std::remove(mProjectiles.begin(), mProjectiles.end(), projectile), mProjectiles.end());
}

const std::vector<ProjectileEnnemi*>& SampleScene::GetProjectiles()
{
	return mProjectiles;
}

#include <iostream>
#include "PistolClass.h"
#include "../ManagerGroup/GameManager.h"

Pistol::Pistol(int Damage, int FireSpeed)
{
	m_PistolDamage = Damage;
	m_PistolFireSpeed = FireSpeed;
}

void Pistol::Use(int linkModule)
{
	if (Clock.getElapsedTime().asMilliseconds() > m_PistolFireSpeed)
	{
		Clock.restart();

		GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Bullet.mp3");
		GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();

		GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(new Bullet(GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->GetModule(linkModule), sf::Vector2f(0.f, 0.7f), 0));
	}
}

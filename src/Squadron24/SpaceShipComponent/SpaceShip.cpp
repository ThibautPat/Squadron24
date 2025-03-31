#include "SpaceShip.h"
#include <iostream>
#include "../ManagerGroup/GameManager.h"

SpaceShip::SpaceShip(int MaxModule, int Faction, int Type)
{
	if (Faction == GameManager::Faction::Gentil)
	{ 
		switch (Type)
		{
		case (0):
		{
			m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::SHIPPLAYER1];
			break;
		}
		case (1) :
		{
			m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::SHIPPLAYER4];
			break;
		}
		case (2):
		{
			m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::SHIPPLAYER3];
			break;
		}
		case (3):
		{
			m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::SHIPPLAYER2];
			m_Sprite.setScale(0.75, 0.75);
			break;
		}
		default:
			break;
		}
	}
	else 
	{
		switch (Type)
		{
		case (0):
		{
			m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::SHIPENNEMIE1];
			break;
		}
		case (1):
		{
			m_Texture = *GameManager::GetInstance()->m_DataManager->m_TextureMap[DataManager::SHIPENNEMIE2];
			m_Sprite.setScale(0.5f, 0.5f);

			break;
		}
		default:
			break;
		}
	}
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setOrigin((float)m_Texture.getSize().x / 2.f, (float)m_Texture.getSize().y / 2.f);

	for (int i = 0; i <= MaxModule; i++)
	{
		m_ModuleEquiped[i] = nullptr;
	}
	m_MaxModule = MaxModule;
}

void SpaceShip::SetModule(int NumSlot, Module* Link)
{
	if (NumSlot > m_MaxModule)
	{
		return;
	}
	m_ModuleEquiped[NumSlot] = Link;
}

Module* SpaceShip::GetModule(int NumSlot)
{
	if (NumSlot > m_MaxModule)
	{
		exit(1);
	}
	return m_ModuleEquiped[NumSlot];
}

void SpaceShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= this->getTransform();
	for (int i = 0; i <= m_MaxModule; i++)
	{
		std::map<int, Module*>::const_iterator moduleprinted = m_ModuleEquiped.find(i);

		if (moduleprinted != m_ModuleEquiped.end() && moduleprinted->second != nullptr) 
		{
			target.draw(moduleprinted->second->m_Sprite, states); 
		}
	}

	target.draw(m_Sprite, states);
}

void SpaceShip::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
	for (int i = 0; i <= m_MaxModule; i++)
	{
		if (m_ModuleEquiped[i] != NULL)
		{
			sf::Vector2f vaisseauPos = m_Sprite.getPosition();

			float modulePosX = vaisseauPos.x + m_ModuleEquiped[i]->decalageX;
			float modulePosY = vaisseauPos.y + m_ModuleEquiped[i]->decalageY;

			m_ModuleEquiped[i]->m_Sprite.setPosition(modulePosX, modulePosY);

			m_ModuleEquiped[i]->m_CooX = this->getPosition().x + m_ModuleEquiped[i]->decalageX;
			m_ModuleEquiped[i]->m_CooY = this->getPosition().y + m_ModuleEquiped[i]->decalageY;
		}
		else
		{
			continue;
		}
	}
}

void SpaceShip::Deplacement(sf::Vector2f direction, sf::Time deltaTime)
{
	this->move(direction.x * deltaTime.asMilliseconds(), direction.y * deltaTime.asMilliseconds());
}

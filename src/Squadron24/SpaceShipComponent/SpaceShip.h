#pragma once
#include <SFML/Graphics.hpp>
#include "Module.h"
#include "../EntityComponent/Character.h"

class SpaceShip : public Character 
{
public:

	sf::Texture m_Texture;

	int m_MaxModule = 0;

	sf::Sprite m_Sprite;

	int m_SelectedSlot = 0;

	std::map<int, Module*> m_ModuleEquiped;

	SpaceShip(int MaxModule, int Faction, int Type);

	void SetModule(int NumSlot, Module* Link);

	Module* GetModule(int NumSlot);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

	void Deplacement(sf::Vector2f direction, sf::Time deltaTime);
};
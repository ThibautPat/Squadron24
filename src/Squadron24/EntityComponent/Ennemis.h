#pragma once
#include "Character.h"
#include "../SpaceShipComponent/SpaceShip.h"
#include <SFML/Graphics.hpp>


class Ennemis : public Character
{
public:
	sf::Clock Clock;

	int m_PatternIndex = 0;
	float m_targetTime = 0;

	std::map<int, sf::Vector2f> m_Path;

	SpaceShip* m_CurrentSpaceShip;

	Ennemis(int health, float targetTime, std::map<int, sf::Vector2f> Path);

	void SetCurrentSpaceShip(SpaceShip* Ship);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

	void AttacLoop();
	void MoveLoopPath(sf::Time deltaTime);
	void IsDead();
};



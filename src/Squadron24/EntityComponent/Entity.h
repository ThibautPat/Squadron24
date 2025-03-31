#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:

	sf::CircleShape* m_HitBox;
	int m_Faction;

	virtual void Update(sf::Time deltaTime, const sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
};


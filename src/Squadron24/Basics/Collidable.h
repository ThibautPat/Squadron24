#pragma once
#include <SFML/Graphics.hpp>

class Collidable {
public:
	virtual bool Hit(sf::CircleShape* TargetCircle, sf::CircleShape* MyCircle);
};
#pragma once
#include "../SpaceShipComponent/SpaceShip.h"
#include "../Basics/Movable.h"
#include "../Basics/IAttacker.h"
#include "../Basics/Collidable.h"
#include "Entity.h"

#include <SFML/Graphics.hpp>

class Bullet: public Collidable, public IAttacker, public Entity
{
protected:

	Module* Originemodule;

	sf::Texture m_Texture;
	sf::Texture m_TextureAnim;
	sf::Sprite m_Sprite;

	bool m_IsExploding = false;

	int m_AnimationFrame = 0;

	sf::Vector2f m_DirectionBullet;
	int m_AngleRotation;

public:

	Bullet(Module* Origine, sf::Vector2f DirectionBullet, int angleRotation);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Movint(sf::Time deltaTime, Module* Originemodule);
	void CollitionUpdate(sf::Time deltaTime);
	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void AnimationExplode(sf::Time deltaTime);
	void attack(Alive*);
	~Bullet();
};
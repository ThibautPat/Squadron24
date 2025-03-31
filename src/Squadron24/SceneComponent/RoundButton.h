#pragma once
#include "../EntityComponent/Entity.h"
class RoundButton:public Entity
{
public:

	sf::Texture m_texture;
	sf::Sprite m_Sprite;

	sf::CircleShape m_buttonShape;

	int m_link;

	RoundButton(float x, float y, float width, float height, const std::string& textureFile);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool isHover(sf::Vector2i mousePosition, const sf::RenderWindow& window);
};


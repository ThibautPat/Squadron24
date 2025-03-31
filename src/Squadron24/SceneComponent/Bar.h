#pragma once
#include "../EntityComponent/Entity.h"

class Bar : public Entity
{
protected:

	sf::Texture m_TextureBack;
	sf::Sprite m_SpriteBack;

	sf::Texture m_TextureSide;
	sf::Sprite m_SpriteSide;

	sf::Texture m_TextureBar;
	sf::Sprite m_SpriteBar;

	float m_Fill;

public:

	Bar(float percentage, float X, float Y, float ScaleX, float ScaleY, std::string BarName);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	float Get();
	void Set(float percentage);
};


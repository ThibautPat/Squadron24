#pragma once
#include "Button.h"
class ButtonGarage : public Button
{
public:

	int m_link;
	int m_R;
	int m_G;
	int m_B;

	ButtonGarage(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B, int link);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


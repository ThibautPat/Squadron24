#pragma once
#include "Button.h"

class BuyButton:public Button
{
public:
	int m_link;
	int m_R;
	int m_G;
	int m_B;
	int m_Price;

	BuyButton(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B, int link, int price);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

};


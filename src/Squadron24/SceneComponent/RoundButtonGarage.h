#pragma once
#include "RoundButton.h"
class RoundButtonGarage : public RoundButton
{
public:

	int m_link;

	RoundButtonGarage(float x, float y, float width, float height, const std::string& textureFile, int link);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

};


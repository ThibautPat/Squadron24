#pragma once
#include "Button.h"
class ButtonSave: public Button
{
public:

	ButtonSave(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

};

#pragma once
#include "RoundButton.h"
#include "TextBox.h"

class RoundButtonMenu : public RoundButton
{
public:

	int m_link;
	bool m_hover = 0;

	TextBox* score;

	sf::Sprite* Rank;
	sf::Texture RankText;

	RoundButtonMenu(float x, float y, float width, float height, const std::string& textureFile, int link);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

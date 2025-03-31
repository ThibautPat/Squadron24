#pragma once
#include <SFML/Graphics.hpp>
#include "../EntityComponent/Entity.h"

class TextBox: public Entity
{
public:

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	sf::Text m_Text;
	sf::Font m_Font;

	std::vector<std::string> m_Lines;

	unsigned int m_police;
	int m_id;

	TextBox(std::string text, std::string texture, float X, float Y, float ScaleX, float ScaleY, unsigned int police, int id);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void Update(sf::Time deltaTime, const sf::RenderWindow& window);

	void splitTextIntoLines(const std::string& text, float boxWidth, unsigned int charSize);
	void SetText(std::string& text);
};


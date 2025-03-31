#pragma once
#include "../EntityComponent/Entity.h"

class Button :public Entity
{
public:

    sf::Texture m_texture;
    sf::Sprite m_Sprite;

    sf::RectangleShape m_buttonShape;

    sf::Text m_text;
    sf::Font m_font;

    float m_ratio;

    Button(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B);

    void Update(sf::Time deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isHover(sf::Vector2i mousePosition, const sf::RenderWindow& window);
    float GetWidth() const;
    float GetHeight() const;
    void SetPosition(float xPercentage, float yPercentage, const sf::RenderWindow& window);
};


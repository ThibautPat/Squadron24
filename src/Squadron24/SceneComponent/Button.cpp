#include "Button.h"
#include "../ManagerGroup/GameManager.h"

Button::Button(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font,int R ,int G , int B) {
    if (!m_texture.loadFromFile("../../../res/"+ textureFile+".png")) 
    {
    }

    if (!m_font.loadFromFile("../../../res/FONT/"+Font+".ttf"))
    {
    }

    m_text.setFont(m_font);
    m_text.setCharacterSize(police);
    m_text.setFillColor(sf::Color(R,G,B,255));
    m_text.setString(text);

    m_ratio = m_texture.getSize().x / (float)(m_texture.getSize().y);

    m_Sprite.setTexture(m_texture);
    m_Sprite.setScale(width, height);
    m_Sprite.setPosition(x, y);

    m_buttonShape.setSize(sf::Vector2f((float)m_texture.getSize().x, (float)m_texture.getSize().y));
    m_buttonShape.setPosition(x, y);
    m_buttonShape.setFillColor(sf::Color::Transparent);
    m_buttonShape.setScale(width, height);
    
}

void Button::Update(sf::Time deltaTime, const sf::RenderWindow& window) 
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(m_buttonShape, states);
    target.draw(m_Sprite, states);
    target.draw(m_text, states);
}

bool Button::isHover(sf::Vector2i mousePosition, const sf::RenderWindow& window) 
{
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
    return m_buttonShape.getGlobalBounds().contains(worldPos);
}

float Button::GetWidth() const
{
    return m_buttonShape.getSize().x;
}

float Button::GetHeight() const
{
    return m_buttonShape.getSize().y;
}

void Button::SetPosition(float xPercentage, float yPercentage, const sf::RenderWindow& window)
{
    float x = xPercentage * window.getSize().x;
    float y = yPercentage * window.getSize().y;

    float width = window.getSize().x * 0.3f;  
    float height = width / m_ratio;

    m_Sprite.setPosition(x, y);
    m_buttonShape.setPosition(x, y);    
    m_buttonShape.setSize(sf::Vector2f(width, height)); 

    m_Sprite.setScale(width / m_Sprite.getLocalBounds().width, height / m_Sprite.getLocalBounds().height);
}


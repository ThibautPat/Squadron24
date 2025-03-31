#include "RoundButton.h"
#include "../ManagerGroup/GameManager.h"
RoundButton::RoundButton(float x, float y, float width, float height, const std::string& textureFile)
{
    if (!m_texture.loadFromFile("../../../res/" + textureFile + ".png")) {
    }
    m_Sprite.setTexture(m_texture);
    m_Sprite.setScale(width, height);
    m_Sprite.setPosition(x, y);

    m_Sprite.setOrigin(m_Sprite.getTextureRect().getSize().x / 2, m_Sprite.getTextureRect().getSize().y/2);
    m_buttonShape.setPosition(x, y);

    m_buttonShape.setOrigin(m_Sprite.getOrigin());

    m_buttonShape.setRadius((float)m_texture.getSize().x/2);

    m_buttonShape.setFillColor(sf::Color::Transparent);
    m_buttonShape.setScale(width, height);
}

void RoundButton::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
}

void RoundButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_Sprite, states);

    target.draw(m_buttonShape, states);
}

bool RoundButton::isHover(sf::Vector2i mousePosition, const sf::RenderWindow& window)
{
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePosition);
    return m_buttonShape.getGlobalBounds().contains(worldPos);
    
    sf::Vector2f center2 = m_buttonShape.getPosition();

    float distance = std::sqrtf(std::powf(center2.x - worldPos.x, 2) + std::powf(center2.y - worldPos.y, 2));

    if (distance <= (m_buttonShape.getRadius()))
    {
        return true;
    }

    return false;
}

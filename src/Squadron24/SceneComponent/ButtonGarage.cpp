#include "ButtonGarage.h"
#include "../ManagerGroup/GameManager.h"
#include "../SpaceShipComponent/PistolClass.h"
#include "../SpaceShipComponent/ShieldClass.h"
#include "../SpaceShipComponent/ShotGunClass.h"

ButtonGarage::ButtonGarage(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B, int link) : Button(x, y, width, height, textureFile, text, police, Font, R, G, B)
{
    m_link = link;
    m_text.setPosition(x+20, y+15);
    m_R = R;
    m_G = G;
    m_B = B;
}

void ButtonGarage::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    sf::Mouse mouse;
    if (m_link == -1)
    {
        m_Sprite.setColor(sf::Color::Red);

        m_text.setFillColor(sf::Color::Red);
    }
    
    if (isHover(mouse.getPosition(window), window) && m_link != -1)
    {
        m_Sprite.setColor(sf::Color::Blue);
        m_text.setFillColor(sf::Color::Blue);

        if (mouse.isButtonPressed(sf::Mouse::Button::Left))
        {
            GameManager::GetInstance()->m_PlayerInstance->ChangePreModule(m_link); 
        }
    }
    else
    {
        if (m_link != -1)
        {
            m_Sprite.setColor(sf::Color::White);
            m_text.setFillColor(sf::Color(m_R, m_G, m_B, 255));
        }

    }
}

void ButtonGarage::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(m_buttonShape, states);
    target.draw(m_Sprite, states);
    target.draw(m_text, states);
}
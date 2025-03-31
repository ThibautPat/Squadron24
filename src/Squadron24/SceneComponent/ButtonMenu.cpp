#include "ButtonMenu.h"
#include "../ManagerGroup/GameManager.h"

ButtonMenu::ButtonMenu(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B, int link):Button( x, y, width,  height,  textureFile,text,police,Font,R,G,B)
{
    m_link = link;
    m_text.setPosition(x+55, y+15);
    m_R = R;
    m_G = G;
    m_B = B;
}
void ButtonMenu::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    sf::Mouse mouse;

    if (isHover(mouse.getPosition(window), window))
    {
        m_Sprite.setColor(sf::Color::Red);
        m_text.setFillColor(sf::Color::Red);
        if (mouse.isButtonPressed(sf::Mouse::Button::Left))
        {
            GameManager::GetInstance()->m_GameState = m_link;

            GameManager::GetInstance()->m_AudioManagerInstance->StopSound();
            GameManager::GetInstance()->m_AudioManagerInstance->ClearCurrentSound();

            GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Select.ogg");
            GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
        }
    }
    else
    {
        m_Sprite.setColor(sf::Color::White);
        m_text.setFillColor(sf::Color(m_R, m_G, m_B, 255));

    }
}
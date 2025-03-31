#include "BuyButton.h"
#include "../ManagerGroup/GameManager.h"

BuyButton::BuyButton(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B, int link,int price) :Button(x, y, width, height, textureFile, text, police, Font, R, G, B)
{
    m_link = link;
    m_text.setPosition(x + 105, y + 15);
    m_R = R;
    m_G = G;
    m_B = B;
    m_Price = price;
}

void BuyButton::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    sf::Mouse mouse;

    if (isHover(mouse.getPosition(window), window))
    {
        m_Sprite.setColor(sf::Color::Red);
        m_text.setFillColor(sf::Color::Red);

        if (mouse.isButtonPressed(sf::Mouse::Button::Left)&& GameManager::GetInstance()->m_PlayerInstance->m_Money >= m_Price && GameManager::GetInstance()->m_CreatedSpaceShipList[m_link].second != 1)
        {
            GameManager::GetInstance()->m_AudioManagerInstance->StopSound();
            GameManager::GetInstance()->m_AudioManagerInstance->ClearCurrentSound();

            GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Select.ogg");
            GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
            GameManager::GetInstance()->m_PlayerInstance->AddSpaceShip(GameManager::GetInstance()->m_PlayerInstance->m_SpaceShipList.size() , GameManager::GetInstance()->m_CreatedSpaceShipList[m_link].first);

            GameManager::GetInstance()->m_CreatedSpaceShipList[m_link].second = 1;

            GameManager::GetInstance()->m_PlayerInstance->m_Money -= m_Price;
        }
        else 
        {
            m_Sprite.setColor(sf::Color(152,154,175));
            m_text.setFillColor(sf::Color(218, 220, 231));
        }
    }
    else
    {
        if (GameManager::GetInstance()->m_CreatedSpaceShipList[m_link].second != 1)
        {
            m_Sprite.setColor(sf::Color::White);
            m_text.setFillColor(sf::Color(m_R, m_G, m_B, 255));
        }
        else 
        {
            m_Sprite.setColor(sf::Color(152, 154, 175));
            m_text.setFillColor(sf::Color(218, 220, 231));
        }
    }
}
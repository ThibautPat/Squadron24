#include "ArrowButtonGarage.h"
#include "../ManagerGroup/GameManager.h"


ArrowButtonGarage::ArrowButtonGarage(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B, int sens) :Button(x, y, width, height, textureFile, text, police, Font, R, G, B)
{

    m_text.setPosition(x + 55, y + 15);
    m_R = R;
    m_G = G;
    m_B = B;
    m_sens = sens;
    clickreset.restart();
}

void ArrowButtonGarage::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    sf::Mouse mouse;

    if (isHover(mouse.getPosition(window), window))
    {
        m_Sprite.setColor(sf::Color::Red);
        m_text.setFillColor(sf::Color::Red);

        if (clickreset.getElapsedTime().asMilliseconds() > 150 && mouse.isButtonPressed(sf::Mouse::Button::Left) && ((GameManager::GetInstance()->m_PlayerInstance->SpaceShipSelect + m_sens >=0 )&&(GameManager::GetInstance()->m_PlayerInstance->SpaceShipSelect + m_sens)<( GameManager::GetInstance()->m_PlayerInstance->m_SpaceShipList.size())))
        {
            GameManager::GetInstance()->m_AudioManagerInstance->StopSound();
            GameManager::GetInstance()->m_AudioManagerInstance->ClearCurrentSound();

            GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Select.ogg");
            GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
            GameManager::GetInstance()->m_PlayerInstance->SpaceShipSelect += m_sens;
            GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->selectedShip+= m_sens;
            GameManager::GetInstance()->m_PlayerInstance->SetCurrentSpaceShip(GameManager::GetInstance()->m_PlayerInstance->SpaceShipSelect);

            clickreset.restart();
        }
    }
    else
    {
        m_Sprite.setColor(sf::Color::White);
        m_text.setFillColor(sf::Color(m_R, m_G, m_B, 255));

    }
}
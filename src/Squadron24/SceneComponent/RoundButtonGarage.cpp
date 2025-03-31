#include "RoundButtonGarage.h"
#include "../ManagerGroup/GameManager.h"
RoundButtonGarage::RoundButtonGarage(float x, float y, float width, float height, const std::string& textureFile, int link) :RoundButton(x, y, width, height, textureFile)
{
    m_link = link;
}
void RoundButtonGarage::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    sf::Mouse mouse;

    if (isHover(mouse.getPosition(window), window)) {

        m_buttonShape.setFillColor(sf::Color::Yellow);
        if (mouse.isButtonPressed(sf::Mouse::Button::Left))
        {
            GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_SelectedSlot = m_link;
        }
    }
    else {
        m_Sprite.setColor(sf::Color::White);
        m_buttonShape.setFillColor(sf::Color::Transparent);

    }
}
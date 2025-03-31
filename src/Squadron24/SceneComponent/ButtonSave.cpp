#include "ButtonSave.h"
#include "../ManagerGroup/GameManager.h"

ButtonSave::ButtonSave(float x, float y, float width, float height, const std::string& textureFile, std::string text, unsigned int police, std::string Font, int R, int G, int B) : Button(x, y, width, height, textureFile, text, police, Font, R, G, B)
{
    m_text.setPosition(x + 150, y);

}
void ButtonSave::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    sf::Mouse mouse;

    if (isHover(mouse.getPosition(window), window))
    {
        m_Sprite.setColor(sf::Color::Red);

        if (mouse.isButtonPressed(sf::Mouse::Button::Left))
        {

            GameManager::GetInstance()->m_AudioManagerInstance->StopSound();
            GameManager::GetInstance()->m_AudioManagerInstance->ClearCurrentSound();

            GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Select.ogg");
            GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();

            GameManager::GetInstance()->m_PlayerInstance->Save();
        }
    }
    else
    {
        m_Sprite.setColor(sf::Color::White);
    }
}
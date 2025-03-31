#include "GarageSpaceShip.h"
#include "../ManagerGroup/GameManager.h"


GarageSpaceShip::GarageSpaceShip(float x, float y, float scale_x, float scale_y, int Rotation)
{
    m_Texture = GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_Sprite.getTexture();

    m_scaleX = scale_x;
    m_scaleY = scale_y;

    m_Sprite.setTexture(*m_Texture);
    m_Sprite.setPosition(x, y);
    m_Sprite.setScale(scale_x, scale_y);
    m_Sprite.setRotation(Rotation);
    m_SlotNumber = new TextBox("Slot N*","UI/Slot",1075,50,0.75,0.75,24,0);
    m_Sprite.setOrigin((float)m_Texture->getSize().x / 2.f, (float)m_Texture->getSize().y / 2.f);
}

void GarageSpaceShip::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{

    slotText = "Slot N*" + std::to_string(GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_SelectedSlot);
    m_SlotNumber->SetText(slotText);

    m_Sprite.setOrigin((float)m_Texture->getSize().x / 2.f, (float)m_Texture->getSize().y / 2.f);

    m_Texture = GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_Sprite.getTexture();
    m_Sprite.setTexture(*m_Texture);
    m_Sprite.setScale(GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_Sprite.getScale().x*2.5, GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_Sprite.getScale().y * 2.5);
    m_Sprite.setTextureRect(GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_Sprite.getTextureRect());

    m_ModulesCopies.clear();

    for (int i = 0; i <= GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_MaxModule; i++)
    {
        std::map<int, Module*>::const_iterator moduleIt = GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_ModuleEquiped.find(i);
        if (moduleIt != GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_ModuleEquiped.end() && moduleIt->second != nullptr)
        {
            Module copiedModule = *moduleIt->second;

            copiedModule.m_Sprite.setScale(m_scaleX, m_scaleY);

            m_ModulesCopies.push_back(copiedModule); 

            sf::Vector2f vaisseauPos = m_Sprite.getPosition();
            sf::Vector2f vaisseauScale = m_Sprite.getScale();
            float modulePosX = vaisseauPos.x + copiedModule.decalageX * vaisseauScale.x;
            float modulePosY = vaisseauPos.y + copiedModule.decalageY * vaisseauScale.y;
            if(m_RoundButtons[i]== nullptr)
            {
                RoundButtonGarage* button = new RoundButtonGarage(modulePosX, modulePosY, 1, 1, "OTHER/slot", i);
                m_RoundButtons[i] = button;
            }
        }
    }

    if(GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->selectedShip != m_selectedShip)
    {
        for (size_t i = 0; i < m_RoundButtons.size(); i++)
        {
            delete m_RoundButtons[i];
        }
        m_RoundButtons.clear();
        m_selectedShip = GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->selectedShip;

    }

    sf::Vector2f vaisseauPos = m_Sprite.getPosition();
    sf::Vector2f vaisseauScale = m_Sprite.getScale();

    for (int i = 0; i <= GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_MaxModule; i++)
    {

            float modulePosX = vaisseauPos.x + m_ModulesCopies[i].decalageX * vaisseauScale.x;
            float modulePosY = vaisseauPos.y + m_ModulesCopies[i].decalageY * vaisseauScale.y;

            m_ModulesCopies[i].m_Sprite.setPosition(modulePosX, modulePosY);

            m_ModulesCopies[i].m_Sprite.setScale(vaisseauScale);

            m_ModulesCopies[i].m_CooX = modulePosX;
            m_ModulesCopies[i].m_CooY = modulePosY;
        

    }

    for (int i = 0; i < m_RoundButtons.size(); i++)
    {
        m_RoundButtons[i]->Update(deltaTime, window);
    }
}

void GarageSpaceShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i = 0; i < m_ModulesCopies.size(); i++)
    {
        target.draw(m_ModulesCopies[i].m_Sprite, states);
    }
    target.draw(m_Sprite, states);

    for (int i = 0; i < m_RoundButtons.size(); i++)
    {
        target.draw(*m_RoundButtons.at(i), states);
    }
    target.draw(*m_SlotNumber);
}


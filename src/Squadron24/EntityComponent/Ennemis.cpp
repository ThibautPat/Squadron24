#include "Ennemis.h"
#include "../ManagerGroup/GameManager.h"
#include <iostream>

Ennemis::Ennemis(int health, float targetTime, std::map<int, sf::Vector2f> Path)
{
    m_CurrentSpaceShip = nullptr;

    m_HitBox = new sf::CircleShape(50.f);
    m_HitBox->setOrigin(50, 50);
    m_HitBox->setFillColor(sf::Color(0, 0, 250, 120));

    m_MaxHealth = health;
    m_ActualHealth = m_MaxHealth;

    m_targetTime = targetTime;
    m_Path = Path; 

    m_Faction = GameManager::Faction::Mechant;
}

void Ennemis::SetCurrentSpaceShip(SpaceShip* Ship)
{
    m_CurrentSpaceShip = Ship;
}

void Ennemis::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(*m_CurrentSpaceShip, states);
}

void Ennemis::AttacLoop()
{    
    if (Clock.getElapsedTime().asSeconds() > 2)
    {

        Clock.restart();

        for (int i = 0; i <= m_CurrentSpaceShip->m_MaxModule; i++)
        {
            if (m_CurrentSpaceShip->GetModule(i)->m_Type == 0)
            {
                GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(new Bullet(m_CurrentSpaceShip->GetModule(i), sf::Vector2f(0, -0.7f), -180));
                GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Bullet.mp3");
                GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
            }
            if (m_CurrentSpaceShip->GetModule(i)->m_Type == 2)
            {
                GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(new Bullet(m_CurrentSpaceShip->GetModule(i), sf::Vector2f(0.f, -0.7f), -180));
                GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Bullet.mp3");
                GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();

                GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(new Bullet(m_CurrentSpaceShip->GetModule(i), sf::Vector2f(0.3f, -0.7f), 140));
                GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Bullet.mp3");
                GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();

                GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->AddEntity(new Bullet(m_CurrentSpaceShip->GetModule(i), sf::Vector2f(-0.3f, -0.7f), -140));
                GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("Bullet.mp3");
                GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();
            }
        }
    }
}

void Ennemis::MoveLoopPath(sf::Time deltaTime)
{
    int pathLength = m_Path.size();
    if (pathLength <= 1) return;

    float totalDistance = pathLength - 1;
    float patternSpeed = (m_targetTime > 0) ? totalDistance / m_targetTime : 0;

    m_PatternIndex += patternSpeed * deltaTime.asSeconds();

    if (m_PatternIndex >= pathLength)
    {
        m_PatternIndex = pathLength - 1;
        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->RemoveEntity(this);
        return;
    }

    if (m_PatternIndex >= 0 && m_PatternIndex < pathLength)
    {
        sf::Vector2f position = m_Path[m_PatternIndex];
        m_HitBox->setPosition(position);
        m_CurrentSpaceShip->setPosition(position);
    }
}

void Ennemis::IsDead()
{
    if (GetHealth() <= 0)
    {
        GameManager::GetInstance()->m_PlayerInstance->AddCurrentLevelScore(50);

        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->RemoveEntity(this);

        GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_RageMultiplicator++;
        if (GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_RageBar < 5)
        {
            GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_RageBar += 1;
        }
    }
}

void Ennemis::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{

    m_CurrentSpaceShip->Update(deltaTime, window); 

    AttacLoop();

    IsDead();
    
    MoveLoopPath(deltaTime);

}
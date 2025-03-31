#include "Player.h"
#include <iostream>
#include "../ManagerGroup/GameManager.h"
#include "../SpaceShipComponent/PistolClass.h"
#include "../SpaceShipComponent/ShieldClass.h"
#include "../SpaceShipComponent/ShotGunClass.h"

Player::Player(int health)
{
    m_CurrentSpaceShip = nullptr;

    m_HitBox = new sf::CircleShape(25.f);
    m_HitBox->setOrigin(25, 25);
    m_HitBox->setFillColor(sf::Color(0, 0, 250, 120));

    m_MaxHealth = health;
    m_ActualHealth = m_MaxHealth;

    m_HealthBar = new Bar(((float)m_ActualHealth / (float)m_MaxHealth), 421, 990,1.85,2,std::string("LifeBar"));
    m_ShieldBar = new Bar(0, 421, 885, 1.85, 2, std::string("ShieldBar"));
    m_RageBar = new Bar(0, 1770, 1075, 0.75, 0.75, std::string("RageBar"));

    playermultiplicatorCLock = new sf::Clock;
    m_lastHealth = m_ActualHealth + m_Shield;

    m_Money = 0;

    m_Faction = GameManager::Faction::Gentil;

    m_LevelUnlock[GameManager::GameState::LEVEL_1] = 1;
    m_LevelUnlock[GameManager::GameState::LEVEL_2] = 0;
    m_LevelUnlock[GameManager::GameState::LEVEL_3] = 0;
    m_LevelUnlock[GameManager::GameState::LEVEL_4] = 0;
    m_LevelUnlock[GameManager::GameState::LEVEL_5] = 0;
    m_LevelUnlock[GameManager::GameState::LEVEL_6] = 0;
    m_LevelUnlock[GameManager::GameState::LEVEL_7] = 0;
    m_LevelUnlock[GameManager::GameState::LEVEL_8] = 0;

    m_LevelsScore[GameManager::GameState::LEVEL_1] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_2] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_3] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_4] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_5] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_6] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_7] = 0;
    m_LevelsScore[GameManager::GameState::LEVEL_8] = 0;
    m_LevelsScore[GameManager::GameState::LEVELINFINI] = 0;
    SpaceShipSelect=0;

    if (!m_ShieldTexture.loadFromFile("../../../res/OTHER/shield3.png"))
    {
    }
    m_ShieldSprite.setTexture(m_ShieldTexture);
    m_ShieldSprite.setOrigin((float)m_ShieldTexture.getSize().x / 2.f, (float)m_ShieldTexture.getSize().y / 2.f);
}

void Player::AddSpaceShip(int id, SpaceShip* Link)
{
    m_SpaceShipList[id] = Link;
}

void Player::SetCurrentSpaceShip(int id)
{
    m_CurrentSpaceShip = m_SpaceShipList[id];
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform(); 
    target.draw(*m_CurrentSpaceShip, states); 

    if (ShieldOn == true)
    {
        target.draw(m_ShieldSprite);
    }
}

void Player::AddCurrentLevelScore(int score)
{
    GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_Score += GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_ScoreMultiplicator * score;
}

void Player::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    m_NumModuleShield = 0;
    m_CurrentSpaceShip->Update(deltaTime, window);
    m_HitBox->setPosition(m_CurrentSpaceShip->getPosition());
    m_ShieldSprite.setPosition(m_CurrentSpaceShip->getPosition());

    m_HealthBar->Set(((float)m_ActualHealth / (float)m_MaxHealth));
    if (m_MAXSHield > 0)
    {
        m_ShieldBar->Set(((float)m_Shield / (float)m_MAXSHield));
    }
    else {
        m_ShieldBar->Set(0);
    }

    m_RageBar->Set(((float)GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_RageBar / (float)5));

    for (int i = 0; i <= m_CurrentSpaceShip->m_MaxModule; i++)
    {
        if (m_CurrentSpaceShip->GetModule(i)->m_Type == 1)
        {
            m_NumModuleShield++;
        }
    }
    if (m_NumModuleShield >= 1)
    {
        ShieldOn = true;
    }
    else 
    {
        ShieldOn = false;
        GameManager::GetInstance()->m_PlayerInstance->m_Shield = 0;
    }
    GameManager::GetInstance()->m_PlayerInstance->m_MAXSHield = 50 * m_NumModuleShield;

    for (int i = 0; i <= GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_MaxModule; i++)
    {
        if (GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->GetModule(i)->m_preModule->Shield)
        {
            GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->GetModule(i)->m_preModule->Use(i);
        }
    }

    float opacity = static_cast<float>(GameManager::GetInstance()->m_PlayerInstance->m_Shield) / 100.0f * 255.0f;
    GameManager::GetInstance()->m_PlayerInstance->m_ShieldSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity)));

}

void Player::ChangePreModule(int m_link)
{
    int tempoSlot = GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_SelectedSlot;
    GameManager::GetInstance()->m_AudioManagerInstance->ChangeSound("InstallModule.mp3");
    GameManager::GetInstance()->m_AudioManagerInstance->PlaySound();

    if (tempoSlot < 0 || tempoSlot > GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_MaxModule)
    {
        return;
    }

    Module* module = GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->GetModule(tempoSlot);
    if (!module)
    {
        return;
    }

    if (module->m_Type == 1)
    {
        Player* player = GameManager::GetInstance()->m_PlayerInstance;
        player->m_MAXSHield -= 50;
        player->m_Shield = 0;
    }

    delete module->m_preModule;

    switch (m_link)
    {
    case 0:
        module->m_preModule = new Pistol(1, 250);
        break;
    case 1:
        module->m_preModule = new ShieldClass(50, 250);
        break;
    case 2:
        module->m_preModule = new ShotGunClass(1, 250);
        break;
    default:
        return;
    }
    module->SetNewPreModuleTexture(m_link);
    module->m_Type = m_link;
}

void Player::ResetBar()
{
    m_ActualHealth = m_MaxHealth;
    m_Shield = m_MAXSHield;
    m_RageBar->Set(0);
}

void Player::SpaceShipCreate(int NumModule)
{
    SpaceShip* Vaisseaux = new SpaceShip(NumModule, GameManager::Faction::Gentil,0);
}

void Player::Save()
{
    std::string nomFichier = "../../../res/SCENE/Save.txt";
    std::ofstream fichier(nomFichier);

    if (!fichier.is_open()) 
    {
    }
    std::string levelUnluck = "";
    for (int i = 8; i < 16; i++)
    {
        levelUnluck += std::to_string(m_LevelUnlock[i]);
        levelUnluck += ";";
    }
    std::string levelscore = "";

    for (int i = 8; i < 17; i++)
    {
        levelscore += std::to_string(m_LevelsScore[i]);
        levelscore += ";";
    }

    std::string ShipUnlock = "";

    for (int i = 0; i < GameManager::GetInstance()->m_CreatedSpaceShipList.size(); i++)
    {

        
        ShipUnlock += std::to_string(GameManager::GetInstance()->m_CreatedSpaceShipList[i].second);
       
        ShipUnlock += ";";
    }

    std::string money = std::to_string(m_Money);
    fichier << "levelUnluck;"+levelUnluck+"\n";
    fichier << "levelscore;"+ levelscore+"\n";
    fichier << "Money;" + money + "\n";
    fichier << "ShipUnlock;" + ShipUnlock + "\n";

    fichier.close();
}

void Player::LoadSave()
{
    std::ifstream file("../../../res/SCENE/Save.txt");
    if (!file.is_open()) {
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string objectType;
        std::getline(stream, objectType, ';');
        if (objectType == "levelUnluck") {
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_1];
            stream.ignore(1, ';');
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_2];
            stream.ignore(1, ';'); 
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_3];
            stream.ignore(1, ';'); 
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_4];
            stream.ignore(1, ';'); 
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_5];
            stream.ignore(1, ';'); 
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_6];
            stream.ignore(1, ';');
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_7];
            stream.ignore(1, ';'); 
            stream >> m_LevelUnlock[GameManager::GameState::LEVEL_8];

        }
        if (objectType == "levelscore") {
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_1];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_2];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_3];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_4];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_5];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_6];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_7];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVEL_8];
            stream.ignore(1, ';'); 
            stream >> m_LevelsScore[GameManager::GameState::LEVELINFINI];
        }
        if (objectType == "Money") {

            stream >> m_Money;
        }
        if (objectType == "ShipUnlock") {
            for (int i = 0; i < GameManager::GetInstance()->m_CreatedSpaceShipList.size(); i++)
            {
                stream >> GameManager::GetInstance()->m_CreatedSpaceShipList[i].second;
                stream.ignore(1, ';'); 

            }
            GameManager::GetInstance()->m_PlayerInstance->m_SpaceShipList.clear();
            for (int i = 0; i < GameManager::GetInstance()->m_CreatedSpaceShipList.size(); i++)
            {
                if (GameManager::GetInstance()->m_CreatedSpaceShipList[i].second == 1)
                {
                    GameManager::GetInstance()->m_PlayerInstance->AddSpaceShip(GameManager::GetInstance()->m_PlayerInstance->m_SpaceShipList.size(), GameManager::GetInstance()->m_CreatedSpaceShipList[i].first);
                }
            }

        }
    }
}
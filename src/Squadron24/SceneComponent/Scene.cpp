#include "Scene.h"
#include <iostream>
#include "../EntityComponent/Entity.h"
#include "../ManagerGroup/GameManager.h"

Scene::Scene(std::string Name, int GameStateName)
{
    std::ifstream file("../../../res/SCENE/" + Name + ".txt");
    if (!file.is_open()) {
        return;
    }
    m_player = 0;
    std::string line;

    while (std::getline(file, line)) 
    {
        std::istringstream stream(line);
        std::string objectType;
        std::getline(stream, objectType, ';');

        if (objectType == "Decor") {
            std::string id;
            double x, y, width, height, rotation, opacity, animated, MaxFrame, Speed, FirstFrame;

            std::getline(stream, id, ';');
            stream >> x;
            stream.ignore(1, ';'); 
            stream >> y;
            stream.ignore(1, ';'); 
            stream >> width;
            stream.ignore(1, ';'); 
            stream >> height;
            stream.ignore(1, ';');
            stream >> rotation;
            stream.ignore(1, ';');
            stream >> opacity;
            stream.ignore(1, ';');
            stream >> animated;
            stream.ignore(1, ';');
            stream >> MaxFrame;
            stream.ignore(1, ';'); 
            stream >> Speed;
            stream.ignore(1, ';'); 
            stream >> FirstFrame;
            Decor* decor = new Decor(id, x, y, width, height, rotation, opacity, animated, MaxFrame, Speed, FirstFrame);
            AddDecor(decor);
        }
        else if (objectType == "Bar")
        {
            AddUI(GameManager::GetInstance()->m_PlayerInstance->m_HealthBar);
            AddUI(GameManager::GetInstance()->m_PlayerInstance->m_ShieldBar);
            AddUI(GameManager::GetInstance()->m_PlayerInstance->m_RageBar);
        }
        else if (objectType=="Sound")
        {
            for (int i = 0; i < 5; i++)
            {
                std::string* sound = new std::string;

                std::getline(stream, *sound, ';');
                if (*sound != " ")
                {
                    m_soundList.push_back(sound);
                }

            }
        }
        else if (objectType == "Clock")
        {
            m_clock = new sf::Clock;
            stream >> m_lvlWinMoney;

        }
        else if (objectType == "Audio")
        {

            for (int i = 0; i < 5; i++)
            {
                std::string* Music = new std::string;

                std::getline(stream, *Music, ';');
                if (*Music != " ")
                {
                    m_MusicList.push_back(Music);
                }

            }
        }
        else  if (objectType == "Player")
        {
            int x, y, AreaLimiteX, AreaLimiteY;
            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> AreaLimiteX; 
            stream.ignore(1, ';');
            stream >> AreaLimiteY;

            m_player = true;

            GameManager::GetInstance()->m_PlayerInstance->m_MAXSHield = 0;
            GameManager::GetInstance()->m_PlayerInstance->m_Shield = 0;

            for (int i = 0; i <= GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->m_MaxModule; i++)
            {
                if (GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->GetModule(i)->m_Type == 1)
                {
                    GameManager::GetInstance()->m_PlayerInstance->m_MAXSHield += 50;
                    GameManager::GetInstance()->m_PlayerInstance->m_Shield = GameManager::GetInstance()->m_PlayerInstance->m_MAXSHield;
                }
            }
            GameManager::GetInstance()->m_PlayerInstance->ResetBar();

            GameManager::GetInstance()->m_PlayerInstance->m_CurrentSpaceShip->setPosition(x, y);

            m_ArreaLimitPlay.x = AreaLimiteX; 
            m_ArreaLimitPlay.y = AreaLimiteY;

            AddEntity(GameManager::GetInstance()->m_PlayerInstance);
        }
        else if (objectType == "Mob")
        {
            int time, x, y, Pattern, Type;
            float TimeScreen;

            stream >> time;
            stream.ignore(1, ';'); 
            stream >> x;
            stream.ignore(1, ';'); 
            stream >> y;
            stream.ignore(1, ';'); 
            stream >> Pattern;
            stream.ignore(1, ';');
            stream >> TimeScreen;
            stream.ignore(1, ';');
            stream >> Type;

            struct MobInfoSpawn MOB; 
            MOB.Pattern = Pattern;
            sf::Vector2f vect(x, y);
            MOB.Position = vect;
            MOB.Time = time;
            MOB.TimeScreen = TimeScreen;
            MOB.Type = Type;

            m_ListeMobInfo[m_ListeMobInfo.size() + 1] = MOB;
        }
        else  if (objectType == "PlayerShip")
        {
            double x, y, width, height,rotation;
            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            stream >> rotation;
            GarageSpaceShip* GarageSpaceShips = new GarageSpaceShip(x, y, width, height, rotation);
            GarageSpaceShips->setScale(width, height);
            AddUI(GarageSpaceShips);

        }
        else if(objectType == "ButtonGarage"){

            double x, y, width, height, police, R, G, B;
            std::string imagePath, text, Font;
            int link;

            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, imagePath, ';');
            std::getline(stream, text, ';');
            stream >> police;
            stream.ignore(1, ';');
            std::getline(stream, Font, ';');
            stream >> R;
            stream.ignore(1, ';');
            stream >> G;
            stream.ignore(1, ';');
            stream >> B;
            stream.ignore(1, ';');
            stream >> link;

            ButtonGarage* Buttongarage = new ButtonGarage(x, y, width, height, imagePath, text, police, Font, R, G, B, link);
            AddUI(Buttongarage);
        }

        else if (objectType == "ArrowButtonGarage") {

            double x, y, width, height, police, R, G, B;
            std::string imagePath, text, Font;
            int sens;

            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, imagePath, ';');
            std::getline(stream, text, ';');
            stream >> police;
            stream.ignore(1, ';');
            std::getline(stream, Font, ';');
            stream >> R;
            stream.ignore(1, ';');
            stream >> G;
            stream.ignore(1, ';');
            stream >> B;
            stream.ignore(1, ';');
            stream >> sens;

            ArrowButtonGarage* Buttongarage = new ArrowButtonGarage(x, y, width, height, imagePath, text, police, Font, R, G, B, sens);
            AddUI(Buttongarage);
            }


        else if (objectType == "BuyButton") {

                double x, y, width, height, police, R, G, B;
                std::string imagePath, text, Font;
                int link, price;

                stream >> x;
                stream.ignore(1, ';');
                stream >> y;
                stream.ignore(1, ';');
                stream >> width;
                stream.ignore(1, ';');
                stream >> height;
                stream.ignore(1, ';');
                std::getline(stream, imagePath, ';');
                std::getline(stream, text, ';');
                stream >> police;
                stream.ignore(1, ';');
                std::getline(stream, Font, ';');
                stream >> R;
                stream.ignore(1, ';');
                stream >> G;
                stream.ignore(1, ';');
                stream >> B;
                stream.ignore(1, ';');
                stream >> link;
                stream.ignore(1, ';');
                stream >> price;

                BuyButton* Button = new BuyButton(x, y, width, height, imagePath, text, police, Font, R, G, B,link, price);
                AddUI(Button);
                }

        else  if (objectType == "RoundButton") {
            double x, y, width, height;
            std::string imagePath;
            int link;

            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, imagePath, ';');
            stream >> link;

            RoundButtonMenu* roundButton = new RoundButtonMenu(x, y, width, height, imagePath, link);
            AddUI(roundButton);
        }
        else if (objectType == "ButtonSave")
        {
            double x, y, width, height, police, R, G, B;
            std::string imagePath, text, Font;

            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, imagePath, ';');
            std::getline(stream, text, ';');
            stream >> police;
            stream.ignore(1, ';');
            std::getline(stream, Font, ';');
            stream >> R;
            stream.ignore(1, ';');
            stream >> G;
            stream.ignore(1, ';');
            stream >> B;
             
            ButtonSave* button = new ButtonSave(x, y, width, height, imagePath, text, police, Font, R, G, B);
            
            AddUI(button);

        }
        else if (objectType == "ButtonLoadSave")
        {
            double x, y, width, height, police, R, G, B;
            std::string imagePath, text, Font;

            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, imagePath, ';');
            std::getline(stream, text, ';');
            stream >> police;
            stream.ignore(1, ';');
            std::getline(stream, Font, ';');
            stream >> R;
            stream.ignore(1, ';');
            stream >> G;
            stream.ignore(1, ';');
            stream >> B;


            ButtonLoadSave* button = new ButtonLoadSave(x, y, width, height, imagePath, text, police, Font, R, G, B);

            AddUI(button);

            }
        else if (objectType == "Button") {
            double x, y, width, height , police , R,G,B;
            std::string imagePath, text, Font;
            int link;

            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, imagePath, ';');
            std::getline(stream, text, ';');
            stream >> police;
            stream.ignore(1, ';');
            std::getline(stream, Font, ';');
            stream >> R;
            stream.ignore(1, ';');
            stream >> G;
            stream.ignore(1, ';');
            stream >> B;
            stream.ignore(1, ';');
            stream >> link;

            ButtonMenu* button = new ButtonMenu(x, y, width, height, imagePath,text,police,Font,R,G,B, link);
            AddUI(button);
        }
        else if (objectType == "Bar") {
            double x, y, width, height, fill;
            std::string type;

            stream >> fill;
            stream.ignore(1, ';');
            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            std::getline(stream, type, ';');

            Bar* bar = new Bar(fill, x, y, width, height, type);
            AddUI(bar);
        }
        else if (objectType == "TextBox") 
        {
            double x, y, width, height, police,id;
            std::string text, texture;

            std::getline(stream, text, ';');
            std::getline(stream, texture, ';');
            stream >> x;
            stream.ignore(1, ';');
            stream >> y;
            stream.ignore(1, ';');
            stream >> width;
            stream.ignore(1, ';');
            stream >> height;
            stream.ignore(1, ';');
            stream >> police;
            stream.ignore(1, ';');
            stream >> id;

            TextBox* textBox = new TextBox(text, texture, x, y, width, height, police,id);
            textBox->setPosition(x, y);
            AddTextBox(textBox);
        }
    }
    file.close();
    GameStateNameLink = GameStateName;
}

void Scene::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    RageBarUpdate(deltaTime);

    for (int i = 0; i < m_EntityList.size(); i++)
    {
        m_EntityList[i]->Update(deltaTime, window);
    }
    for (int i = 0; i < m_DecorList.size(); i++)
    {
        m_DecorList[i]->Update(deltaTime, window);
    }
    for (int i = 0; i < m_UIList.size(); i++)
    {
        m_UIList[i]->Update(deltaTime, window);
    }
    for (int i = 0; i < m_TextBoxList.size(); i++)
    {
        m_TextBoxList[i]->Update(deltaTime, window);
    }
    if (m_clock != nullptr)
    {
        LevelUpdate();
    }
}

void Scene::RageBarUpdate(sf::Time deltaTime)
{
    if (m_RageBar > 5)
    {
        m_RageBar = 5;
    }
    if (m_RageBar >= 0)
    {
        m_RageBar -= 0.3 * deltaTime.asSeconds();
    }
    else
    {
        m_ScoreMultiplicator = 1;

        m_RageMultiplicator = 0;
    }

    m_ScoreMultiplicatorCombine = m_RageMultiplicator + m_ScoreMultiplicator;
}

void Scene::LevelUpdate()
{
    if (m_clock->getElapsedTime().asSeconds() > 240)
    {
        GameManager::GetInstance()->m_PlayerInstance->m_LevelUnlock[GameManager::GetInstance()->m_GameState + 1] = 1;
        GameManager::GetInstance()->m_PlayerInstance->m_LevelsScore[GameManager::GetInstance()->m_GameState] = m_Score;
        GameManager::GetInstance()->m_PlayerInstance->m_Money += m_lvlWinMoney;
        m_EntityList.clear();
        GameManager::GetInstance()->m_SceneManagerInstance->NewScene(GameManager::GetInstance()->m_SceneManagerInstance->m_sceneName[GameManager::GameState::WIN], GameManager::GameState::WIN);
        GameManager::GetInstance()->m_SceneManagerInstance->ChangeScene(GameManager::GameState::WIN);
        GameManager::GetInstance()->m_SceneManagerInstance->m_CurrentScene->m_Score = m_Score;
        GameManager::GetInstance()->m_GameState = GameManager::GameState::WIN;
    }
    if (GameManager::GetInstance()->m_PlayerInstance->GetHealth() <= 0)
    {
        m_EntityList.clear();
        GameManager::GetInstance()->m_SceneManagerInstance->NewScene(GameManager::GetInstance()->m_SceneManagerInstance->m_sceneName[GameManager::GameState::GAMEOVER], GameManager::GameState::GAMEOVER);
        GameManager::GetInstance()->m_SceneManagerInstance->ChangeScene(GameManager::GameState::GAMEOVER);
        GameManager::GetInstance()->m_SceneManagerInstance->m_CurrentScene->m_Score = m_Score;
        GameManager::GetInstance()->m_GameState = GameManager::GameState::GAMEOVER;
    }

    for (auto it = m_ListeMobInfo.begin(); it != m_ListeMobInfo.end();)
    {
        if (m_clock->getElapsedTime().asSeconds() >= it->second.Time)
        {
            PatternManager::InitPattern(it->second.Pattern, it->second.TimeScreen, it->second.Type);
            it = m_ListeMobInfo.erase(it);
        }
        else
        {
            ++it;
        }
    }

    if (GameManager::GetInstance()->m_PlayerInstance->m_lastHealth == GameManager::GetInstance()->m_PlayerInstance->GetHealth() + GameManager::GetInstance()->m_PlayerInstance->m_Shield && m_ScoreMultiplicator < 10)
    {
        m_ScoreMultiplicator += GameManager::GetInstance()->m_PlayerInstance->playermultiplicatorCLock->getElapsedTime().asSeconds() / 4800;
    }

    else if (GameManager::GetInstance()->m_PlayerInstance->m_lastHealth != GameManager::GetInstance()->m_PlayerInstance->GetHealth() + GameManager::GetInstance()->m_PlayerInstance->m_Shield)
    {
        GameManager::GetInstance()->m_PlayerInstance->m_lastHealth = GameManager::GetInstance()->m_PlayerInstance->GetHealth() + GameManager::GetInstance()->m_PlayerInstance->m_Shield;
        if (GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_RageBar >= 0.8)
        {
            GameManager::GetInstance()->m_SceneManagerInstance->GetCurrentScene()->m_RageBar -= 0.8;
        }
    }

}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{

    for (int i = 0; i < m_DecorList.size(); i++)
    {
        target.draw(*m_DecorList[i], states);
    }
    for (int i = 0; i < m_EntityList.size(); i++)
	{
		target.draw(*m_EntityList[i], states);
	}
    for (int i = 0; i < m_TextBoxList.size(); i++)
    {
        target.draw(*m_TextBoxList[i], states);
    }
    for (int i = 0; i < m_UIList.size(); i++)
    {
        target.draw(*m_UIList[i], states);
    }
}

void Scene::AddDecor(Entity* decor)
{
	m_DecorList.push_back(decor);
}

void Scene::AddUI(Entity* UI)
{
	m_UIList.push_back(UI);
}

void Scene::AddEntity(Entity* Entity)
{
	m_EntityList.push_back(Entity);
}

void Scene::AddTextBox(TextBox* Entity)
{
    m_TextBoxList.push_back(Entity);
}

void Scene::RemoveEntity(Entity* entityToRemove)
{
    for (int i = 0; i < m_EntityList.size(); ++i)
    {
        if (m_EntityList[i] == entityToRemove)
        {
            m_EntityList.erase(m_EntityList.begin() + i);
            delete entityToRemove; 
            return;
        }
    }
}

Scene::~Scene()
{
    if (m_clock != nullptr)
    {
        delete m_clock;
        m_clock = nullptr;
    }

    for (auto it = m_DecorList.begin(); it != m_DecorList.end();) {
        delete *it;
        it = m_DecorList.erase(it); 
    }

    for (auto it = m_EntityList.begin(); it != m_EntityList.end();) {
        delete* it;
        it = m_EntityList.erase(it);
    }

    for (auto it = m_UIList.begin(); it != m_UIList.end();) {
        delete* it;
        it = m_UIList.erase(it);
    }
    for (auto it = m_TextBoxList.begin(); it != m_TextBoxList.end();) {
        delete* it;
        it = m_TextBoxList.erase(it);
    }
    for (auto it = m_soundList.begin(); it != m_soundList.end();) {
        delete* it;
        it = m_soundList.erase(it);
    }
    for (auto it = m_MusicList.begin(); it != m_MusicList.end();) {
        delete* it;
        it = m_MusicList.erase(it);
    }
}


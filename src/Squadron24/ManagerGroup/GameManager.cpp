#include "GameManager.h"

GameManager* GameManager::m_Instance = nullptr;

GameManager* GameManager::GetInstance()
{
    if (m_Instance == nullptr)
    {
        m_Instance = new GameManager();
    }
    return m_Instance;
}

void GameManager::InitGameManager()
{
    SpaceShip* Vaisseaux1 = new SpaceShip(1, GameManager::Faction::Gentil, 0);
    Vaisseaux1->setPosition(300, 200);

    Module* myModule1 = new Module(-25.f, 0.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux1->SetModule(0, myModule1);

    Module* myModule2 = new Module(25.0f, 0.0f, 1, 250, GameManager::Faction::Gentil,0);
    Vaisseaux1->SetModule(1, myModule2);

    m_Instance->m_CreatedSpaceShipList[0] = std::pair(Vaisseaux1,1);

    SpaceShip* Vaisseaux2 = new SpaceShip(3, GameManager::Faction::Gentil, 1);
    Vaisseaux2->setPosition(300, 200);

    Module* myModule3 = new Module(-20.f, -10.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux2->SetModule(0, myModule3);

    Module* myModule4 = new Module(20.0f, -10.0f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux2->SetModule(1, myModule4);

    Module* myModule5 = new Module(-40.f, 10.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux2->SetModule(2, myModule5);

    Module* myModule6 = new Module(40.0f,10.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux2->SetModule(3, myModule6);

    m_Instance->m_CreatedSpaceShipList[1] = std::pair(Vaisseaux2,0);

    SpaceShip* Vaisseaux3 = new SpaceShip(4, GameManager::Faction::Gentil, 2);
    Vaisseaux3->setPosition(300, 200);

    Module* myModule7 = new Module(-20.f, -10.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux3->SetModule(1, myModule7);

    Module* myModule8 = new Module(20.0f, -10.0f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux3->SetModule(2, myModule8);

    Module* myModule9 = new Module(-40.f, 5.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux3->SetModule(0, myModule9);

    Module* myModule10 = new Module(40.0f, 5.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux3->SetModule(3, myModule10);

    Module* myModule11 = new Module(0.f, -25.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux3->SetModule(4, myModule11);

    m_Instance->m_CreatedSpaceShipList[2] = std::pair(Vaisseaux3,0);

    SpaceShip* Vaisseaux4 = new SpaceShip(4, GameManager::Faction::Gentil, 3);
    Vaisseaux4->setPosition(300, 200);

    Module* myModule12= new Module(-20.f, -20.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux4->SetModule(1, myModule12);

    Module* myModule13 = new Module(20.0f, -20.0f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux4->SetModule(3, myModule13);

    Module* myModule14= new Module(-40.f,-20.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux4->SetModule(0, myModule14);

    Module* myModule15 = new Module(40.0f, -20.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux4->SetModule(4, myModule15);

    Module* myModule16 = new Module(0.0f, -70.f, 1, 250, GameManager::Faction::Gentil, 0);
    Vaisseaux4->SetModule(2, myModule16);

    m_Instance->m_CreatedSpaceShipList[3] = std::pair(Vaisseaux4, 0 ) ;
}

void GameManager::Input(sf::Time deltatime, SpaceShip* Vaisseaux)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        if (Vaisseaux->getPosition().y > 0)
        {
            Vaisseaux->Deplacement({ 0, -0.5f }, deltatime);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (Vaisseaux->getPosition().y < m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_ArreaLimitPlay.y)
        {
            Vaisseaux->Deplacement({ 0, 0.5f }, deltatime);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        if (Vaisseaux->getPosition().x > 0)
        {
            Vaisseaux->Deplacement({ -0.5f, 0 }, deltatime);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (Vaisseaux->getPosition().x < m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_ArreaLimitPlay.x)
        {
            Vaisseaux->Deplacement({ 0.5f, 0 }, deltatime);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_player == true)
    {
        for (int i = 0; i <= m_Instance->m_PlayerInstance->m_CurrentSpaceShip->m_MaxModule; i++)
        {
            if (!m_Instance->m_PlayerInstance->m_CurrentSpaceShip->GetModule(i)->m_preModule->Shield)
            {
                m_Instance->m_PlayerInstance->m_CurrentSpaceShip->GetModule(i)->m_preModule->Use(i);
            }
        }
    }
}

void GameManager::VerifScene()
{
    if (m_Instance->m_SceneManagerInstance->m_SceneMap[m_Instance->m_GameState] != m_Instance->m_SceneManagerInstance->GetCurrentScene()) 
    {
        delete m_Instance->m_SceneManagerInstance->m_SceneMap[0]; 

        m_Instance->m_SceneManagerInstance->m_SceneMap.clear(); 
        m_Instance->m_SceneManagerInstance->NewScene(m_Instance->m_SceneManagerInstance->m_sceneName[m_Instance->m_GameState], m_Instance->m_GameState); 

        m_Instance->m_SceneManagerInstance->ChangeScene(m_Instance->m_GameState); 

        if (m_Instance->m_GameState != m_Instance->m_AudioManagerInstance->m_GameState) 
        {

            m_Instance->m_AudioManagerInstance->m_GameState = m_Instance->m_GameState; 

            m_Instance->m_AudioManagerInstance->StopSound();
            m_Instance->m_AudioManagerInstance->StopCurrentMusic();

            m_Instance->m_AudioManagerInstance->ClearCurrentSound();
            m_Instance->m_AudioManagerInstance->ClearCurrentMusic();

            m_Instance->m_AudioManagerInstance->AddLevelSound(m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_soundList);
            m_Instance->m_AudioManagerInstance->AddLevelMusic(m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_MusicList);

            m_Instance->m_AudioManagerInstance->PlaySound();
            m_Instance->m_AudioManagerInstance->PlayCurrentMusic();
        }
    }
}

int GameManager::GameLoop()
{
    m_Instance->m_DataManager = new DataManager();
    m_Instance->m_DataManager->InitData();
    m_Instance->InitGameManager();
    m_Instance->m_PatternManager = new PatternManager();

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Squadron 24", sf::Style::Fullscreen);

    sf::Image icon;
    icon.loadFromFile("../../../res/OTHER/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); 

    window.setFramerateLimit(30);

    sf::Clock Clock;
    GameManager::GetInstance()->m_ClockTime = Clock;

    sf::Time deltatime;
    deltatime = Clock.restart();

    m_Instance->m_PlayerInstance = new Player(100);
    m_Instance->m_PlayerInstance->AddSpaceShip(0, m_Instance->m_CreatedSpaceShipList[0].first);
    m_Instance->m_PlayerInstance->SetCurrentSpaceShip(0);

    m_Instance->m_SceneManagerInstance = new SceneManager();
    m_Instance->m_SceneManagerInstance->NewScene(m_Instance->m_SceneManagerInstance->m_sceneName[MENU], GameManager::MENU);
    m_Instance->m_SceneManagerInstance->ChangeScene(MENU);

    m_Instance->m_AudioManagerInstance = new AudioManager();
    m_Instance->m_AudioManagerInstance->AddLevelSound(m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_soundList);
    m_Instance->m_AudioManagerInstance->AddLevelMusic(m_Instance->m_SceneManagerInstance->GetCurrentScene()->m_MusicList);

    m_Instance->m_AudioManagerInstance->PlaySound();
    m_Instance->m_AudioManagerInstance->PlayCurrentMusic();

    GameManager::GetInstance()->m_PlayerInstance->LoadSave();

    while (window.isOpen())
    {
        deltatime = Clock.restart();
        sf::Event event;

        VerifScene();
        
        Input(deltatime, m_Instance->m_PlayerInstance->m_CurrentSpaceShip); 

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                GameManager::m_Instance->m_PlayerInstance->Save();
                delete m_Instance->m_AudioManagerInstance;
                return 0;
            }
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        m_Instance->m_SceneManagerInstance->GetCurrentScene()->Update(deltatime, window);

        window.clear(sf::Color(2, 14, 65)); // Print le background avec la couleurs bleu

        window.draw(*m_Instance->m_SceneManagerInstance->GetCurrentScene());

        window.display();

        if (m_Instance->m_GameState == EXIT)
        {
            GameManager::m_Instance->m_PlayerInstance->Save();
            delete m_Instance->m_AudioManagerInstance;
            return 0;
        }
    }
}

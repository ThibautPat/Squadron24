#include "SceneManager.h"
#include "GameManager.h"

SceneManager::SceneManager() 
{

    m_sceneName[GameManager::GameState::MENU]="Menu";
    m_sceneName[GameManager::GameState::STATION] = "Play";
    m_sceneName[GameManager::GameState::SETTING] = "Settings";
    m_sceneName[GameManager::GameState::MAP1] = "Map";
    m_sceneName[GameManager::GameState::MARKET] = "Market";
    m_sceneName[GameManager::GameState::LEVELINFINI] = "Infinie";
    m_sceneName[GameManager::GameState::GARAGE] = "Garage";
    m_sceneName[GameManager::GameState::PAUSE] = "menuList";
    m_sceneName[GameManager::GameState::MAP2] = "Map2";
    m_sceneName[GameManager::GameState::LEVEL_1] = "Level1";
    m_sceneName[GameManager::GameState::LEVEL_2] = "Level2";
    m_sceneName[GameManager::GameState::LEVEL_3] = "Level3";
    m_sceneName[GameManager::GameState::LEVEL_4] = "Level4";
    m_sceneName[GameManager::GameState::LEVEL_5] = "Level5";
    m_sceneName[GameManager::GameState::LEVEL_6] = "Level6";
    m_sceneName[GameManager::GameState::LEVEL_7] = "Level7";
    m_sceneName[GameManager::GameState::LEVEL_8] = "Level8";
    m_sceneName[GameManager::GameState::GAMEOVER] = "GameOver";
    m_sceneName[GameManager::GameState::WIN] = "Win";

}

Scene* SceneManager::GetCurrentScene()
{
	return m_CurrentScene;
}

void SceneManager::ChangeScene(int scene)
{
	m_CurrentScene = m_SceneMap[scene];
}

void SceneManager::NewScene(std::string Name, int GameStateName)
{
    Scene* newScene = new Scene(Name, GameStateName);
    m_SceneMap[GameStateName] = newScene;
}

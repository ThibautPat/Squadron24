#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Basics/Collidable.h"
#include "../SceneComponent/TextBox.h"
#include "../SceneComponent/Bar.h"
#include "../SpaceShipComponent/SpaceShip.h"
#include "../SceneComponent/Button.h"
#include "../EntityComponent/Bullet.h"
#include "../SceneComponent/Scene.h"
#include "../ManagerGroup/SceneManager.h"
#include "../ManagerGroup/AudioManager.h"
#include "../EntityComponent/Player.h"
#include "../EntityComponent/Ennemis.h"
#include "../SceneComponent/RoundButton.h"
#include "PatternManager.h"
#include "DataManager.h"

class GameManager
{
public:

	static GameManager* m_Instance;

	enum GameState
	{
		MENU,
		PAUSE,
		SETTING,
		MAP1, 
		MAP2,
		STATION,
		MARKET,
		GARAGE,
		LEVEL_1,
		LEVEL_2,
		LEVEL_3,
		LEVEL_4,
		LEVEL_5,
		LEVEL_6,
		LEVEL_7,
		LEVEL_8, 
		LEVELINFINI,
		EXIT,
		GAMEOVER,
		WIN
	};

	enum Faction
	{
		Gentil,
		Mechant
	};

	int m_GameState = MENU;

	sf::Clock m_ClockTime;

	std::map<int, std::pair<SpaceShip*, bool>>m_CreatedSpaceShipList{};

	Player* m_PlayerInstance;
	SceneManager* m_SceneManagerInstance;
	AudioManager* m_AudioManagerInstance;
	PatternManager* m_PatternManager;
	DataManager* m_DataManager;

	static GameManager* GetInstance();

	void InitGameManager();

	void Input(sf::Time deltatime, SpaceShip* Vaisseaux);
	void VerifScene();
	int GameLoop();
};


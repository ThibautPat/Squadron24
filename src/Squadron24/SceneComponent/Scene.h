#pragma once
#include <vector>
#include "../EntityComponent/Entity.h"
#include "Decor.h"
#include "ButtonMenu.h"
#include "Bar.h"
#include "TextBox.h"
#include "RoundButtonMenu.h"
#include "GarageSpaceShip.h"
#include "ButtonGarage.h"
#include "ButtonSave.h"
#include "ButtonLoadSave.h"
#include "ArrowButtonGarage.h"
#include "BuyButton.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>      
#include <sstream>

struct MobInfoSpawn
{
	int Time;
	sf::Vector2f Position;
	int Pattern;
	int Type;
	float TimeScreen;
};

class Scene:public sf::Drawable
{
public:

	sf::Clock* m_clock = nullptr;
	bool m_player;

	std::vector<Entity*> m_UIList;
	std::vector<Entity*> m_DecorList;
	std::vector<TextBox*> m_TextBoxList;
	std::vector<Entity*> m_EntityList;

	std::map<int, MobInfoSpawn> m_ListeMobInfo;

	std::vector<std::string*> m_soundList;
	std::vector<std::string*> m_MusicList;

	float m_Score = 0;
	float m_ScoreMultiplicatorCombine = 1;
	float m_ScoreMultiplicator = 1;
	float m_RageMultiplicator = 1;
	float m_RageBar = 0;

	int m_lvlWinMoney = 0;
	int selectedShip=0;

	int GameStateNameLink = 0;

	sf::Vector2i m_ArreaLimitPlay;

	Scene(std::string Name, int GameStateName);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void RageBarUpdate(sf::Time deltaTime);
	void LevelUpdate();

	void AddDecor(Entity* decor);
	void AddUI(Entity* UI);
	void AddEntity(Entity* Entity);
	void AddTextBox(TextBox* Entity);

	void RemoveEntity(Entity* entityToRemove);
	~Scene();
};



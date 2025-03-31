#pragma once
#include "Character.h"
#include "../SpaceShipComponent/SpaceShip.h"
#include <SFML/Graphics.hpp>
#include "../SceneComponent/Bar.h"

class Player : public Character
{
public:

	bool ShieldOn = false;

	int m_NumModuleShield = 0;
	int m_lastHealth;
	int SpaceShipSelect;
	int m_Money;

	sf::Texture m_ShieldTexture;
	sf::Sprite m_ShieldSprite;

	Bar* m_HealthBar;
	Bar* m_ShieldBar;
	Bar* m_RageBar;

	sf::Clock* playermultiplicatorCLock;

	std::map<int, SpaceShip*> m_SpaceShipList{};
	std::map<int,bool> m_LevelUnlock{};
	std::map<int, int> m_LevelsScore{};
	std::map<int, PreModule*> m_listePreModule{};

	SpaceShip* m_CurrentSpaceShip;

	Player(int health);

	void AddSpaceShip(int id, SpaceShip* Link);
	void SetCurrentSpaceShip(int id);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void AddCurrentLevelScore(int score);
	void ChangePreModule(int m_link);
	void ResetBar();
	void SpaceShipCreate(int NumModule) override;
	void Save();
	void LoadSave();

};
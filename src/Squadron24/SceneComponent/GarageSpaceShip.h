#pragma once
#include "../EntityComponent/Entity.h"
#include "../SpaceShipComponent/Module.h"
#include "RoundButtonGarage.h"
#include "TextBox.h"
#include <SFML/Graphics.hpp>
#include <vector>
class GarageSpaceShip: public Entity
{
public:

	float m_scaleX;
	float m_scaleY;

	int m_selectedShip = 0;

	const sf::Texture* m_Texture;
	sf::Sprite m_Sprite;

	std::vector <Module> m_ModulesCopies;
	std::map <int,RoundButton*> m_RoundButtons;

	TextBox* m_SlotNumber;
	std::string slotText;

	GarageSpaceShip( float x, float y, float scale_x, float scale_y, int Rotation);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


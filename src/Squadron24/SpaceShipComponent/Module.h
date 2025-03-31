#pragma once
#include "SFML/Graphics.hpp"
#include "PreModule.h"

class Module : public sf::Transformable
{
public: 
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	float m_CooX = 0;
	float m_CooY = 0;

	float decalageX = 0;
	float decalageY = 0;

	int m_Faction;
	int m_Type;

	PreModule* m_preModule;

	Module(float X, float Y, int Param1, int Param2, int Faction, int Type);

	void SetNewPreModuleTexture(int Type);
};



#pragma once
#include <iostream>
#include "unordered_map"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class DataManager
{
public:

	enum Data
	{
		GREENBULLET,
		REDBULLET,
		GREENHITANIMATION,
		REDHITANIMATION,
		SHIPPLAYER1,
		SHIPPLAYER2,
		SHIPPLAYER3,
		SHIPPLAYER4,
		SHIPENNEMIE1,
		SHIPENNEMIE2,
		SHIPENNEMIE3,
	};

	std::unordered_map<int, sf::Texture*> m_TextureMap{};

	void InitData();
};


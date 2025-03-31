#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class PatternManager
{
public:
	
	sf::Clock clock;
	std::map<int, std::map<int, sf::Vector2f> > ListPath;

	PatternManager();

	static void DrawPatternPath(const std::map<int, sf::Vector2f>& patternPath, sf::RenderWindow& window);
	static bool ValidatePointList(const std::map<int, sf::Vector2f>& PointList);
	static void CurveBezier(const std::map<int, sf::Vector2f>& PointList, std::map<int, sf::Vector2f>& Link);
	static void InitPattern(int Link, float TimeScreen, int Type);
};







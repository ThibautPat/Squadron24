#pragma once
#include <SFML/Graphics.hpp>
#include "../EntityComponent/Entity.h"

class Decor: public Entity {
public:

	sf::Texture m_Texture;
	sf::Sprite m_Sprite;

	int m_animated;
	int m_ActualFrame;
	int m_MaxFrame;
	float m_FrameDuration;          
	float m_TimeSinceLastFrame;
	int m_FramesSize;
	int m_XOrigin;
	int m_YOrigin;	

	std::string m_Animation;

	Decor(std::string name, float x, float y, float scale_x, float scale_y, int Rotation, int opacity, int animated, int MaxFrame, float Speed, int FirstFrame);

	void Update(sf::Time deltaTime, const sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void Animation(sf::Time deltaTime);
	void RotationAnimation(sf::Time deltaTime);
	void ScrollAnimation(sf::Time deltaTime);
	void Respawn(sf::Time deltaTime, const sf::RenderWindow& window);
};
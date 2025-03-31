
#include "Decor.h"
#include "../ManagerGroup/GameManager.h"

Decor::Decor(std::string name,float x , float y , float scale_x, float scale_y, int Rotation,int opacity, int animated,int MaxFrame, float Speed, int FirstFrame)
{
    if (!m_Texture.loadFromFile("../../../res/" + name +".png"))
    {
        exit(1);
    }
    m_XOrigin = x;
    m_YOrigin = y;
    m_Texture.setSmooth(1);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setPosition(x, y);
    m_Sprite.setScale(scale_x, scale_y);
    m_Sprite.setRotation(Rotation);
    m_Sprite.setColor(sf::Color(255, 255, 255, opacity));
    m_animated = animated;
    m_MaxFrame = MaxFrame;
    m_ActualFrame = FirstFrame;
    m_FrameDuration = Speed;
    m_TimeSinceLastFrame = 0.f;
    m_FramesSize = m_Texture.getSize().x / m_MaxFrame;
    m_Sprite.setTextureRect(sf::IntRect(0, 0, m_FramesSize, m_Texture.getSize().y));
}

void Decor::Update(sf::Time deltaTime, const sf::RenderWindow& window)
{
    switch (m_animated)
    {
    case 1:
    {
        Animation(deltaTime);
        break;
    }
    case 2:
    {
        m_Sprite.setOrigin(m_Sprite.getTextureRect().getSize().x / 2, m_Sprite.getTextureRect().getSize().y / 2);

        RotationAnimation(deltaTime);

        break;
    }
    case 3:
    {
        m_Sprite.setOrigin(m_Sprite.getTextureRect().getSize().x / 2, m_Sprite.getTextureRect().getSize().y / 2);

        ScrollAnimation(deltaTime);
        Respawn(deltaTime, window);
        Animation(deltaTime);
        RotationAnimation(deltaTime);
        break;
    }
    case 4:
    {
        m_Sprite.setOrigin(m_Sprite.getTextureRect().getSize().x / 2, m_Sprite.getTextureRect().getSize().y / 2);
        ScrollAnimation(deltaTime);
        Respawn(deltaTime, window);
        RotationAnimation(deltaTime);
        break;
    }
    default:
        break;
    }
}

void Decor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Sprite,states);
}

void Decor::Animation(sf::Time deltaTime)
{
    m_TimeSinceLastFrame += deltaTime.asSeconds();

    if (m_TimeSinceLastFrame >= m_FrameDuration) 
    {
        m_TimeSinceLastFrame -= m_FrameDuration;

        m_ActualFrame = (m_ActualFrame + 1) % m_MaxFrame;

        m_Sprite.setTextureRect(sf::IntRect(m_FramesSize * m_ActualFrame, 0, m_FramesSize, m_Texture.getSize().y));
    }
}

void Decor::RotationAnimation(sf::Time deltaTime)
{
    m_Sprite.setRotation(m_Sprite.getRotation()+ 400* m_FrameDuration * deltaTime.asSeconds());
}

void Decor::ScrollAnimation(sf::Time deltaTime)
{
    m_Sprite.move(0,  400*m_FrameDuration * deltaTime.asSeconds());
}

void Decor::Respawn(sf::Time deltaTime, const sf::RenderWindow& window)
{
    if (window.getSize().y < m_Sprite.getPosition().y)
    {
        m_Sprite.setPosition(m_XOrigin, m_YOrigin);
    }
}


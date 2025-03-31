#include "Bar.h"
Bar::Bar(float percentage, float X, float Y, float ScaleX, float ScaleY, std::string BarName)
{
    if (!m_TextureBack.loadFromFile("../../../res/BAR/"+BarName+"Back.png"))
    {
    }
    if (!m_TextureSide.loadFromFile("../../../res/BAR/" +BarName+"Side.png"))
    {
    }
    if (!m_TextureBar.loadFromFile("../../../res/BAR/"+BarName+".png"))
    {
    }

    m_TextureBack.setSmooth(10);
    m_TextureSide.setSmooth(10);
    m_TextureBar.setSmooth(10);

    m_SpriteBack.setTexture(m_TextureBack);
    m_SpriteSide.setTexture(m_TextureSide);
    m_SpriteBar.setTexture(m_TextureBar);

    if (BarName == "RageBar")
    {
        m_SpriteBack.setPosition(X + (-2.5* ScaleX), Y + (-11.5* ScaleY));
        m_SpriteBar.setPosition(X + (-3* ScaleX), Y + (-16* ScaleY));
        m_SpriteBack.setRotation(-147);
        m_SpriteBar.setRotation(-147);
        m_SpriteSide.setRotation(-147);
    }
    else
    {
        m_SpriteBack.setPosition(X +(5 * ScaleX), Y+(5 * ScaleY));
        m_SpriteBar.setPosition(X +(5 * ScaleX), Y +(5.5* ScaleY) );
    }

    m_SpriteBar.setOrigin(m_SpriteBar.getScale().x / 2, m_SpriteBar.getScale().y / 2);
    m_SpriteSide.setPosition(X, Y);

    m_SpriteBack.setScale(ScaleX, ScaleY);
    m_SpriteSide.setScale(ScaleX, ScaleY);
    m_SpriteBar.setScale(ScaleX , ScaleY);

    m_Fill = percentage;
    m_SpriteBar.setTextureRect(sf::IntRect(0, 0, m_TextureBar.getSize().x * (uint32_t)m_Fill, m_TextureBar.getSize().y));
}

float Bar::Get()
{
    return m_Fill;
}

void Bar::Set(float percentage)
{   
    if (percentage >= 0)
    {
        m_Fill = percentage;
    }
}

void Bar::Update(sf::Time deltaTime, const sf::RenderWindow& window) {
    
    m_SpriteBar.setTextureRect(sf::IntRect(0, 0, (int)(m_TextureBar.getSize().x * m_Fill), m_TextureBar.getSize().y));
    
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_SpriteBack, states);
    target.draw(m_SpriteBar, states);

    target.draw(m_SpriteSide, states);
}
#include "DataManager.h"

void DataManager::InitData()
{
    sf::Texture* m_Texture = new sf::Texture;  
    if (!m_Texture->loadFromFile("../../../res/OTHER/laserGreen11.png"))   
    {
    }
    m_TextureMap[DataManager::GREENBULLET] = m_Texture;  

    sf::Texture* m_Texture2 = new sf::Texture; 
    if (!m_Texture2->loadFromFile("../../../res/OTHER/laserRed01.png")) 
    { 
    } 
    m_TextureMap[DataManager::REDBULLET] = m_Texture2;  

    sf::Texture* m_Texture3 = new sf::Texture;
    if (!m_Texture3->loadFromFile("../../../res/OTHER/HitAllierSpriteSheet.png"))
    {
    }
    m_TextureMap[DataManager::GREENHITANIMATION] = m_Texture3;

    sf::Texture* m_Texture4 = new sf::Texture;
    if (!m_Texture4->loadFromFile("../../../res/OTHER/HitEnnemiSpriteSheet.png"))
    {
    }
    m_TextureMap[DataManager::REDHITANIMATION] = m_Texture4;

    sf::Texture* m_Texture5 = new sf::Texture;
    if (!m_Texture5->loadFromFile("../../../res/OTHER/PlayerShip4.png"))
    {
    }
    m_TextureMap[DataManager::SHIPPLAYER1] = m_Texture5; 

    sf::Texture* m_Texture6 = new sf::Texture;
    if (!m_Texture6->loadFromFile("../../../res/OTHER/PlayerShip3.png"))
    {
    }
    m_TextureMap[DataManager::SHIPPLAYER2] = m_Texture6;

    sf::Texture* m_Texture7 = new sf::Texture;
    if (!m_Texture7->loadFromFile("../../../res/OTHER/PlayerShip2.png"))
    {
    }
    m_TextureMap[DataManager::SHIPPLAYER3] = m_Texture7;

    sf::Texture* m_Texture8 = new sf::Texture;
    if (!m_Texture8->loadFromFile("../../../res/OTHER/PlayerShip1.png"))
    {
    }
    m_TextureMap[DataManager::SHIPPLAYER4] = m_Texture8;

    sf::Texture* m_Texture9 = new sf::Texture;
    if (!m_Texture9->loadFromFile("../../../res/OTHER/EnnemieShip1.png"))
    {
    }
    m_TextureMap[DataManager::SHIPENNEMIE1] = m_Texture9;

    sf::Texture* m_Texture10 = new sf::Texture;
    if (!m_Texture10->loadFromFile("../../../res/OTHER/EnnemieShip2.png"))
    {
    }
    m_TextureMap[DataManager::SHIPENNEMIE2] = m_Texture10;

    sf::Texture* m_Texture11 = new sf::Texture;
    if (!m_Texture11->loadFromFile("../../../res/OTHER/EnnemieShip3.png"))
    {
    }
    m_TextureMap[DataManager::SHIPENNEMIE3] = m_Texture11;
}

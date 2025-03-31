#include "Module.h"
#include "PistolClass.h"
#include "ShieldClass.h"
#include "ShotGunClass.h"
#include "../ManagerGroup/GameManager.h"
#include <iostream>

Module::Module(float X, float Y, int Param1, int Param2, int Faction, int Type)
{
    m_Type = Type;
    switch (Type)
    {
    case(0):
    {
        m_preModule = new Pistol(Param1, Param2);
        if (!m_Texture.loadFromFile("../../../res/OTHER/GunModule.png"))
        {
        }
        break;
    }
    case(1):
    {
        m_preModule = new ShieldClass(Param1, Param2);
        if (!m_Texture.loadFromFile("../../../res/OTHER/ShieldModule.png"))
        {
        }
        break;
    }
    case(2):
    {
        m_preModule = new ShotGunClass(Param1, Param2);
        if (!m_Texture.loadFromFile("../../../res/OTHER/ShootGunModule.png"))
        {
        }
        break;
    }
    default:
        break;
    }
    m_Faction = Faction; 
    decalageX = X;
    decalageY = Y;

    m_Sprite.setTexture(m_Texture);
    m_Sprite.setOrigin((float)m_Texture.getSize().x / 2.f, (float)m_Texture.getSize().y / 2.f);
}

void Module::SetNewPreModuleTexture(int Type)
{
    switch (Type)
    {
    case(0):
    {
        if (!m_Texture.loadFromFile("../../../res/OTHER/GunModule.png"))
        {
        }
        break;
    }
    case(1):
    {
        if (!m_Texture.loadFromFile("../../../res/OTHER/ShieldModule.png"))
        {
        }
        break;
    }
    case(2):
    {
        if (!m_Texture.loadFromFile("../../../res/OTHER/ShootGunModule.png"))
        {
        }
        break;
    }
    default:
        break;
    }
    m_Sprite.setTexture(m_Texture); 
}
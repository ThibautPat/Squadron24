#pragma once
#include <SFML/Graphics.hpp>

class PreModule 
{
protected:

    sf::Clock Clock;

public:

    int m_ShieldValue = 0;
    int m_ShieldregenSpeed = 0;

    int m_PistolDamage = 0;
    int m_PistolFireSpeed = 0;

    bool Shield = false;

    virtual void Use(int linkModule) = 0;
    virtual ~PreModule() = default;
};
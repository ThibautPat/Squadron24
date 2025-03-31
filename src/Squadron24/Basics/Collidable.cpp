#include <cmath>
#include "Collidable.h"
#include <iostream>

bool Collidable::Hit(sf::CircleShape* TargetCircle, sf::CircleShape* MyCircle)
{
    if (TargetCircle == nullptr || MyCircle == nullptr ||MyCircle == TargetCircle)
    {
       return false;
    }

    sf::Vector2f center1 = TargetCircle->getPosition();
    sf::Vector2f center2 = MyCircle->getPosition();

    float distance = std::sqrtf(std::powf(center2.x - center1.x, 2) + std::powf(center2.y - center1.y, 2));

    if (distance <= (MyCircle->getRadius() + TargetCircle->getRadius()))
    {
        return true;
    }

    return false;  
}

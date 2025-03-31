#pragma once

#include "../Basics/Alive.h"
#include "../Basics/Collidable.h"
#include "../Basics/IAttacker.h"
#include "Entity.h"


class Character : public Alive, public Collidable, public IAttacker, public Entity
{
public:

	float posX; 
	float posY;

	void attack(Alive*);
	virtual void SpaceShipCreate(int NumModule);

};

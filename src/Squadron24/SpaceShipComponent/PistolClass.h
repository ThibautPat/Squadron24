#pragma once
#include "PreModule.h"

class Pistol : public PreModule 
{

public:
    Pistol(int Damage, int FireSpeed);

    void Use(int linkModule) override;
};
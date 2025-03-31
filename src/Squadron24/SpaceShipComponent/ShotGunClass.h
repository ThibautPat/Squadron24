#pragma once
#include "PreModule.h"

class ShotGunClass : public PreModule
{

public:
    ShotGunClass(int Damage, int FireSpeed);

    void Use(int linkModule) override;
};
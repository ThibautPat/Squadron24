#pragma once
#include "PreModule.h"

class ShieldClass : public PreModule
{
protected:

public:

    ShieldClass(int Value, int regenSpeed);

    void Use(int linkModule) override;
};
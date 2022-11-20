/// @file   ShipStats.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// C++ includes
#include <cstdint>

namespace Game
{
    struct ShipStats
    {
        uint32_t curHp = 22'301,  curShield = 8'282,   curAmmo = 75'987,  curCargo = 157'984;
        uint32_t maxHp = 236'000, maxShield = 320'000, maxAmmo = 220'000, maxCargo = 999'999;
        uint16_t curRockets = 7'045, maxRockets = 16'000;
    };
} // !namespace Game

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
        static constexpr uint32_t curHp      = 236'000;
        static constexpr uint32_t maxHp      = 236'000;

        static constexpr uint32_t curShield  = 320'000;
        static constexpr uint32_t maxShield  = 320'000;

        static constexpr uint32_t curAmmo    = 220'000;
        static constexpr uint32_t maxAmmo    = 220'000;

        static constexpr uint32_t curRockets =  16'000;
        static constexpr uint32_t maxRockets =  16'000;

        static constexpr uint32_t curCargo   = 999'999;
        static constexpr uint32_t maxCargo   = 999'999;
    };
} // !namespace Game

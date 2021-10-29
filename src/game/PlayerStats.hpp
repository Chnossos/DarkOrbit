/// @file   PlayerStats.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// C++ includes
#include <cstdint>

namespace Game
{
    struct PlayerStats
    {
        uint64_t xp = 1'999'888'777'666, honor = 111'222'333, credits = 999'999'999;
        uint32_t uridium = 99'999'999;
        uint16_t jackpot = 10'000;
    };
} // !namespace Game

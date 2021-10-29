/// @file   Formulas.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "Formulas.hpp"

uint8_t Formulas::getLevelFromXp(uint64_t xp)
{
    uint8_t lvl = 1;
    while (xp >= 10'000)
    {
        xp /= 2;
        ++lvl;
    }
    return lvl;
}

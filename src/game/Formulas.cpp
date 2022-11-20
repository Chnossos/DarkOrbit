/// @file   Formulas.cpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#include "Formulas.hpp"

// C++ includes
#include <cmath>

uint8_t Formulas::getLevelFromXp(uint64_t xp)
{
    return static_cast<uint8_t>(2 + std::log2l(static_cast<long double>(xp) / 10'000));
}

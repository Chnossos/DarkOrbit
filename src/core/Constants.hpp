/// @file   Constants.hpp
/// @author Pierre Caissial
/// @date   Created on 28/10/2021

#pragma once

#define LIST_OF_CONSTANTS                                                          \
    CONSTANT(char const *, windowTitle,    "Dark Orbit");                          \
    CONSTANT(unsigned int, gameViewWidth,  820);                                   \
    CONSTANT(unsigned int, gameViewHeight, 615);                                   \
    CONSTANT(float,        gameViewRatio,  (float)gameViewWidth / gameViewHeight); \
    CONSTANT(unsigned int, fontSize,       10);

// -------------------------------------------------------------------------------------------------

#define CONSTANT(type, name, value) extern type const name

namespace Constants { LIST_OF_CONSTANTS }

#undef CONSTANT

/// @file   Constants.hpp
/// @author Pierre Caissial
/// @date   Created on 28/10/2021

#pragma once

namespace Constants
{
    constexpr char const * windowTitle      = "Dark Orbit";
    constexpr unsigned int gameViewWidth    = 820;
    constexpr unsigned int gameViewHeight   = 615;
    constexpr float        gameViewRatio    = (float)gameViewWidth / gameViewHeight;
    constexpr char const * fontFamily       = "spectrashell.ttf";
    constexpr char const * nbFontFamily     = "GALSB.ttf";
    constexpr unsigned int labelFontSize    = 14;
    constexpr unsigned int subLabelFontSize = 12;
    constexpr unsigned int valueFontSize    = 11;
    constexpr unsigned int nbFontSize       = 10;

    constexpr auto startY  = 4;
    constexpr auto spacing = 4;
} // !namespace Constants

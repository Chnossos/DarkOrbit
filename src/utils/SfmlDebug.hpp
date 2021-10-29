/// @file   SfmlDebug.hpp
/// @author Pierre Caissial
/// @date   Created on 29/10/2021

#pragma once

// Third-party includes
#include <spdlog/fmt/ostr.h>

// C++ includes
#include <iosfwd>

namespace sf
{
    template<typename T> class Rect;
    using FloatRect = Rect<float>;

    std::ostream & operator<<(std::ostream & os, FloatRect const & rect);
} // !namespace sf

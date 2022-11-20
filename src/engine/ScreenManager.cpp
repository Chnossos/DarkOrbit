/// @file   ScreenManager.cpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#include "ScreenManager.hpp"

// Project includes
#include "Screen.hpp"

using namespace Engine;

namespace
{
    class EmptyScreen : public Screen {};
} // !namespace

ScreenManager::ScreenManager()
{
    _screens.push(std::make_shared<EmptyScreen>());
}

auto ScreenManager::size() const -> std::size_t
{
    return _screens.size() - 1;
}

auto ScreenManager::push(BaseScreenPtr ptr) -> Screen &
{
    if (!empty())
        _screens.top()->pause();

    _screens.push(std::move(ptr));
    _screens.top()->enter();
    return *_screens.top();
}

void ScreenManager::pop()
{
    if (!empty())
    {
        _screens.top()->exit();
        _screens.pop();

        if (!empty())
            _screens.top()->resume();
    }
}

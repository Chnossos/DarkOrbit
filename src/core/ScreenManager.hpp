/// @file   ScreenManager.hpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#pragma once

// Project includes
#include "Screen.hpp"

// C++ includes
#include <memory>
#include <stack>

namespace Core
{
    class ScreenManager
    {
        template<class T>
        using ScreenPtr     = std::shared_ptr<T>;
        using BaseScreenPtr = ScreenPtr<Screen>;

    private:
        std::stack<BaseScreenPtr> _screens;

    public:
        ScreenManager();

    public:
        template<class T, typename... Args>
        auto push(Args &&... args) -> T &;
        void pop();

    public:
        [[nodiscard]] auto top()   const -> BaseScreenPtr { return _screens.top(); }
        [[nodiscard]] auto size()  const -> std::size_t;
        [[nodiscard]] bool empty() const { return size() == 0; }

    private:
        auto push(BaseScreenPtr ptr) -> Screen &;
    };

    template<class T, typename... Args>
    inline auto ScreenManager::push(Args && ... args) -> T &
    {
        static_assert(std::is_base_of_v<Screen, T>, "T must inherit Core::Screen");
        return static_cast<T &>(push(std::make_shared<T>(std::forward<Args>(args)...)));
    }
} // !namespace Core

/// @file   Exception.hpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#pragma once

// Third-party includes
#include <fmt/format.h>

// C++ includes
#include <exception>
#include <filesystem>
#include <vector>

namespace Core
{
    /// Extends @c std::exception with string formatting
    struct Exception : public std::runtime_error
    {
        template<typename... Args>
        explicit Exception(fmt::format_string<Args...> str, Args &&... args)
            : std::runtime_error(fmt::format(std::move(str), std::forward<Args>(args)...))
        {}
    };

    template<typename... Args>
    [[noreturn]] inline void throwWithNested(fmt::format_string<Args...> str, Args &&... args)
    {
        std::throw_with_nested(Exception(std::move(str), std::forward<Args>(args)...));
    }

    template<typename... Args>
    [[noreturn]] inline void throwWithNested(int line, std::string const & src,
                                             fmt::format_string<Args...> str, Args &&... args)
    {
        auto const msg = fmt::format(std::move(str), std::forward<Args>(args)...);
        std::throw_with_nested(Exception("{} [{}:{}]", msg, src, line));
    }

#define THROW_NESTED(...) \
    Core::throwWithNested(__LINE__, std::filesystem::path(__FILE__).filename().string(), __VA_ARGS__)

    /// Boolean assert: Throws an error formatted with @p format and @p args if @p expr is false
    template<typename... Args>
    inline void bAssert(bool ok, fmt::format_string<Args...> str, Args &&... args)
    {
        if (!ok) throw Exception(std::move(str), std::forward<Args>(args)...);
    }

    /// Status code assertion. Throws a formatted error if @p code is not 0
    template<typename... Args>
    inline void cAssert(int code, fmt::format_string<Args...> str, Args &&... args)
    {
        bAssert(code == 0, std::move(str), std::forward<Args>(args)...);
    }

    template<typename F, typename... Args>
    inline void eAssert(F && func, fmt::format_string<Args...> str, Args &&... args) try
    {
        func();
    }
    catch (...)
    {
        throwWithNested(std::move(str), std::forward<Args>(args)...);
    }

    using ExceptionStack = std::vector<std::string>;

    auto getExceptionStack(std::exception const & e) -> ExceptionStack;

    auto formatExceptionStack(ExceptionStack const & stack, bool prefixFirstException = false,
                              int indent = 0, int increment = 1, std::string_view prefix = " * ",
                              std::string_view suffix = "\n") -> std::string;

    inline auto formatExceptionStack(std::exception const & e, bool prefixFirstException = false,
                                     int indent = 0, int increment = 1,
                                     std::string_view prefix = " * ",
                                     std::string_view suffix = "\n") -> std::string
    {
        return formatExceptionStack(getExceptionStack(e), prefixFirstException, indent, increment,
                                    prefix, suffix);
    }

//    void printExceptionStack(std::exception const & e, std::ostream & out = std::cerr,
//                             int indent = 0, int increment = 1,
//                             std::string const & prefix = " * ", std::string const & suffix = "\n");
} // !namespace Core

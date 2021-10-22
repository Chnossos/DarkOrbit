/// @file   Exception.cpp
/// @author Pierre Caissial
/// @date   Created on 22/10/2021

#include "Exception.hpp"

namespace
{
    void unstackExceptions(std::exception const & e, Core::ExceptionStack & stack)
    {
        stack.emplace_back(e.what());
        try
        {
            std::rethrow_if_nested(e);
        }
        catch (std::exception const & nested)
        {
            unstackExceptions(nested, stack);
        }
    }
} // !namespace

auto Core::getExceptionStack(std::exception const & e) -> ExceptionStack
{
    ExceptionStack stack;
    unstackExceptions(e, stack);
    return stack;
}

auto Core::formatExceptionStack(Core::ExceptionStack const & stack, bool prefixFirstException,
                                int indent, int increment,
                                std::string_view prefix, std::string_view suffix) -> std::string
{
    std::string result;
    if (!stack.empty())
    {
        if (prefixFirstException)
        {
            result = fmt::format("{:>{}}", prefix, static_cast<int>(prefix.size()) + indent);
            indent += increment;
        }
        result += fmt::format("{}{}", stack[0], suffix);

        for (size_t i = 1; i < stack.size(); ++i, indent += increment)
            result += fmt::format("{:>{}}{}{}", prefix, static_cast<int>(prefix.size()) + indent,
                                  stack[i], suffix);
    }
    return result;
}

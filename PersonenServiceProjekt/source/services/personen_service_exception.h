//
// Created by JoachimWagner on 13.12.2022.
//

#pragma once

#include <exception>
#include <stdexcept>
#include <string>

// Portable (MSVC / GCC / Clang): only uses standard std::runtime_error and
// std::exception_ptr instead of MSVC-specific std::exception constructors.
class personen_service_exception : public std::runtime_error
{
    std::exception_ptr nested;

public:
    personen_service_exception()
            : std::runtime_error("")
    {
    }

    explicit personen_service_exception(std::string const& message)
            : std::runtime_error(message)
    {
    }

    explicit personen_service_exception(char const* message)
            : std::runtime_error(message)
    {
    }

    // Wraps another exception; its message is taken over.
    explicit personen_service_exception(std::exception const& other)
            : std::runtime_error(other.what()), nested(std::current_exception())
    {
    }

    personen_service_exception(std::string const& message, std::exception const& /*other*/)
            : std::runtime_error(message), nested(std::current_exception())
    {
    }

    // Original exception (valid when constructed inside a catch block), else nullptr.
    std::exception_ptr getNested() const noexcept {
        return nested;
    }
};

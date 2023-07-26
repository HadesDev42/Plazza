/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** BaseExceptions
*/

#include "BaseExceptions.hpp"

namespace plazza {
    BaseExceptions::BaseExceptions(std::string message) : _message(message)
    {
    }

    const char *BaseExceptions::what() const noexcept
    {
        return _message.c_str();
    }
}

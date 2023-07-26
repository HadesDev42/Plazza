/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** ThreadExceptions
*/

#include "ThreadExceptions.hpp"

namespace plazza {
    ThreadExceptions::ThreadExceptions(std::string message) : _message(message)
    {
    }

    const char *ThreadExceptions::what() const noexcept
    {
        return _message.c_str();
    }
}
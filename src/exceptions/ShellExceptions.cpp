/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** ShellExceptions
*/

#include "ShellExceptions.hpp"

namespace plazza {
    ShellExceptions::ShellExceptions(std::string message) : _message(message)
    {
    }

    const char *ShellExceptions::what() const noexcept
    {
        return _message.c_str();
    }
}
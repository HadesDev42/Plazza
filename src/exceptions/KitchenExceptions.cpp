/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** KitchenExceptions
*/

#include "KitchenExceptions.hpp"

namespace plazza {
    KitchenExceptions::KitchenExceptions(std::string message) : _message(message)
    {
    }

    const char *KitchenExceptions::what() const noexcept
    {
        return _message.c_str();
    }
}

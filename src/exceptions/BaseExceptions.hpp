/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** BaseExceptions
*/

#pragma once
#include <iostream>
#include <string>
#include <exception>

namespace plazza {
    class BaseExceptions : public std::exception {
        public:
            BaseExceptions(std::string message);
            const char *what() const noexcept override;
        private:
            std::string _message;
    };
}

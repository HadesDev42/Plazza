/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** ThreadExceptions
*/

#pragma once
#include <iostream>

namespace plazza {
    class ThreadExceptions : public std::exception {
        public:
            ThreadExceptions(std::string message);
            const char *what() const noexcept override;
        private:
            std::string _message;
    };
}

/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** MargaritaPizza
*/

#pragma once
#include "APizza.hpp"

namespace plazza {
    class MargaritaPizza : virtual public APizza {
        public:
            MargaritaPizza();
            MargaritaPizza(int nb);
            ~MargaritaPizza();
    };
}
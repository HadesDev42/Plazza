/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** FantasiaPizza
*/

#pragma once
#include "APizza.hpp"

namespace plazza {
    class FantasiaPizza : virtual public APizza {
        public:
            FantasiaPizza();
            FantasiaPizza(int nb);
            ~FantasiaPizza();
    };
}
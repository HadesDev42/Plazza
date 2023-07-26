/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** AmericanaPizza
*/

#pragma once
#include "APizza.hpp"

namespace plazza {
    class AmericanaPizza : virtual public APizza {
        public:
            AmericanaPizza();
            AmericanaPizza(int nb);
            ~AmericanaPizza();
    };
}
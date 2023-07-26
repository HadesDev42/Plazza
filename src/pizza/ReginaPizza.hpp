/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** ReginaPizza
*/

#pragma once
#include "APizza.hpp"

namespace plazza {
    class ReginaPizza : virtual public APizza {
        public:
            ReginaPizza();
            ReginaPizza(int nb);
            ~ReginaPizza();
    };
}
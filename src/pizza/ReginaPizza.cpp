/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** ReginaPizza
*/

#include "ReginaPizza.hpp"

namespace plazza {
    ReginaPizza::ReginaPizza()
    {
        this->_cookTime = 2;
        this->_quantity = 0;
        this->_type = PizzaType::Regina;
        this->_ingredients = {
            .doe = 1,
            .ham = 1,
            .steak = 0,
            .tomato = 1,
            .gruyere = 1,
            .eggplant = 0,
            .mushrooms = 1,
            .chiefLove = 0,
            .goatCheese = 0,
        };
    }

    ReginaPizza::ReginaPizza(int nb)
    {
        this->_cookTime = 2;
        this->_quantity = nb;
        this->_type = PizzaType::Regina;
        this->_ingredients = {
            .doe = 1,
            .ham = 1,
            .steak = 0,
            .tomato = 1,
            .gruyere = 1,
            .eggplant = 0,
            .mushrooms = 1,
            .chiefLove = 0,
            .goatCheese = 0,
        };
    }

    ReginaPizza::~ReginaPizza()
    {
    }
}

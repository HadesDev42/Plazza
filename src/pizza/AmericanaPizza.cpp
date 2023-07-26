/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** AmericanaPizza
*/

#include "AmericanaPizza.hpp"

namespace plazza {
    AmericanaPizza::AmericanaPizza()
    {
        this->_cookTime = 2;
        this->_quantity = 0;
        this->_type = PizzaType::Americana;
        this->_ingredients = {
            .doe = 1,
            .ham = 0,
            .steak = 1,
            .tomato = 1,
            .gruyere = 1,
            .eggplant = 0,
            .mushrooms = 0,
            .chiefLove = 0,
            .goatCheese = 0,
        };
    }

    AmericanaPizza::AmericanaPizza(int nb)
    {
        this->_cookTime = 2;
        this->_quantity = nb;
        this->_type = PizzaType::Americana;
        this->_ingredients = {
            .doe = 1,
            .ham = 0,
            .steak = 1,
            .tomato = 1,
            .gruyere = 1,
            .eggplant = 0,
            .mushrooms = 0,
            .chiefLove = 0,
            .goatCheese = 0,
        };
    }

    AmericanaPizza::~AmericanaPizza()
    {
    }
}

/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** MargaritaPizza
*/

#include "MargaritaPizza.hpp"

namespace plazza {
    MargaritaPizza::MargaritaPizza()
    {
        this->_cookTime = 1;
        this->_quantity = 0;
        this->_type = PizzaType::Margarita;
        this->_ingredients = {
            .doe = 1,
            .ham = 0,
            .steak = 0,
            .tomato = 1,
            .gruyere = 1,
            .eggplant = 0,
            .mushrooms = 0,
            .chiefLove = 0,
            .goatCheese = 0,
        };
    }

    MargaritaPizza::MargaritaPizza(int nb)
    {
        this->_cookTime = 1;
        this->_quantity = nb;
        this->_type = PizzaType::Margarita;
        this->_ingredients = {
            .doe = 1,
            .ham = 0,
            .steak = 0,
            .tomato = 1,
            .gruyere = 1,
            .eggplant = 0,
            .mushrooms = 0,
            .chiefLove = 0,
            .goatCheese = 0,
        };
    }

    MargaritaPizza::~MargaritaPizza()
    {
    }
}

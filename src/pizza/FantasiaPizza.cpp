/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** FantasiaPizza
*/

#include "FantasiaPizza.hpp"

namespace plazza {
    FantasiaPizza::FantasiaPizza()
    {
        this->_cookTime = 4;
        this->_quantity = 0;
        this->_type = PizzaType::Fantasia;
        this->_ingredients = {
            .doe = 1,
            .ham = 0,
            .steak = 0,
            .tomato = 1,
            .gruyere = 0,
            .eggplant = 1,
            .mushrooms = 0,
            .chiefLove = 1,
            .goatCheese = 1,
        };
    }

    FantasiaPizza::FantasiaPizza(int nb)
    {
        this->_cookTime = 4;
        this->_quantity = nb;
        this->_type = PizzaType::Fantasia;
        this->_ingredients = {
            .doe = 1,
            .ham = 0,
            .steak = 0,
            .tomato = 1,
            .gruyere = 0,
            .eggplant = 1,
            .mushrooms = 0,
            .chiefLove = 1,
            .goatCheese = 1,
        };
    }

    FantasiaPizza::~FantasiaPizza()
    {
    }
}

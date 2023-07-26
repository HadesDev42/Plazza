/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** Pizza
*/

#pragma once

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8,
        None = 16
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    struct Ingredients {
        int doe;
        int ham;
        int steak;
        int tomato;
        int gruyere;
        int eggplant;
        int mushrooms;
        int chiefLove;
        int goatCheese;
    };
}
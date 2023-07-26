/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** factory
*/

#pragma once
#include <memory>
#include "../pizza/IPizza.hpp"

namespace plazza {
    class Factory {
        public:
            std::shared_ptr<IPizza> createPizza(PizzaType type);
    };
}

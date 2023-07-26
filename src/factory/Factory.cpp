/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** Factory
*/

#include "Factory.hpp"
#include "../pizza/ReginaPizza.hpp"
#include "../pizza/MargaritaPizza.hpp"
#include "../pizza/FantasiaPizza.hpp"
#include "../pizza/AmericanaPizza.hpp"

namespace plazza {

    std::shared_ptr<IPizza> Factory::createPizza(PizzaType type) {
        switch (type) {
            case PizzaType::Regina:
                return std::make_shared<ReginaPizza>();
            case PizzaType::Margarita:
                return std::make_shared<MargaritaPizza>();
            case PizzaType::Americana:
                return std::make_shared<AmericanaPizza>();
            case PizzaType::Fantasia:
                return std::make_shared<FantasiaPizza>();
            default:
                return nullptr;
        }
    }
}

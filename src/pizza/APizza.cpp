/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** APizza
*/

#include "APizza.hpp"

namespace plazza {

    int APizza::getCookTime() const
    {
        return _cookTime;
    }

    int APizza::getQuantity() const
    {
        return _quantity;
    }

    PizzaType APizza::getType() const
    {
        return _type;
    }

    Ingredients APizza::getIngredients() const
    {
        return _ingredients;
    }

    void APizza::addQuantity(int nb)
    {
        _quantity += nb;
    }

    void APizza::removeQuantity(int nb)
    {
        _quantity -= nb;
    }

    std::string APizza::getName() const
    {
        if (_type == PizzaType::Americana)
            return "americana";
        if (_type == PizzaType::Fantasia)
            return "fantasia";
        if (_type == PizzaType::Margarita)
            return "margarita";
        if (_type == PizzaType::Regina)
            return "regina";
        return "";
    }

    void APizza::setToZero()
    {
        _quantity = 0;
    }
}

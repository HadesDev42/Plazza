/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** IPizza
*/

#pragma once
#include <map>
#include <string>
#include "EnumPizza.hpp"

namespace plazza {
    class IPizza {
        public:
            virtual ~IPizza() = default;
            virtual int getCookTime() const = 0;
            virtual int getQuantity() const = 0;
            virtual PizzaType getType() const = 0;
            virtual Ingredients getIngredients() const = 0;
            virtual void addQuantity(int nb) = 0;
            virtual void removeQuantity(int nb) = 0;
            virtual std::string getName() const = 0;
            virtual void setToZero() = 0;
    };
}
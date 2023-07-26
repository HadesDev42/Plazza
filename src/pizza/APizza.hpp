/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** APizza
*/

#pragma once
#include "IPizza.hpp"
#include <string>

namespace plazza {
    class APizza : virtual public IPizza {
        public:
            virtual ~APizza() = default;
            virtual int getCookTime() const;
            virtual int getQuantity() const;
            virtual PizzaType getType() const;
            virtual Ingredients getIngredients() const;
            virtual void addQuantity(int nb);
            virtual void removeQuantity(int nb);
            virtual std::string getName() const;
            virtual void setToZero();
        protected:
            int _quantity;
            int _cookTime;
            PizzaType _type;
            Ingredients _ingredients;
    };
}

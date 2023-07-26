/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** Reception
*/

#pragma once
#include "../pizza/EnumPizza.hpp"
#include "../ipc/IPC.hpp"
#include "BaseExceptions.hpp"
#include "ShellExceptions.hpp"
#include "KitchenExceptions.hpp"
#include "../factory/Factory.hpp"
#include "../kitchen/Kitchen.hpp"
#include <map>
#include <regex>
#include <mutex>
#include <cmath>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/select.h>

#define ALL_KITCHEN 50

namespace plazza {
    class Reception {
        public:
            Reception() = default;
            Reception(float multiplier, int cooksPerKitchen, int replaceIngredientsTime);
            ~Reception() = default;
            void sendOrder();
            void setToZero();
            void launchShell();
            void printStatus();
            void printOrders();
            void checkCommands();
            void printOrdersList();
            void handleMessageFromKitchens();
            void printPizza(PizzaType pizza);
            void sendPizzaToKitchen(PizzaType type);
            void removeFromCommand(PizzaType type);
            int getNbKitchenToCreate();
            int shouldCreateKitchens();
            int getOrder(std::string getInput);
            int getNumberPizza(std::map<PizzaType, int> pizza);
            int listOrder(std::string order, std::string size, int number);
            int calculateNumberOfKitchens(int numberOfCooks, int givenNumberOfPizzas);
            PizzaType getPizzaToCook();
            PizzaType getTypePizzaFromString(std::string name);
            std::string getMessageToSend();
            std::string getSizePizza(PizzaSize size);
            std::string getTypePizzaFromType(PizzaType type);
            std::vector<std::string> splitString(const std::string& input, char delimiter);

            std::map<PizzaType, int> addCommand();
        protected:
        private:
            int _index;
            int _multiplier;
            int _indexCommand;
            int _cooksPerKitchen;
            int _availableKitchens;
            int _nbOfPizzaPerKitchen;
            int _replaceIngredientsTime;
            std::vector<int> _kitchenList;
            std::mutex _statueMutex;
            std::string _tempString;
            std::vector<std::string> _tempVector;
            std::vector<std::vector<std::string>> _commands;
            std::map<PizzaType, std::map<PizzaSize, int>> _ordersList;
            std::map<PizzaType, std::shared_ptr<IPizza>> _pizzas;
            std::vector<std::map<PizzaType, int>> _pizzaCommands;
            Factory _factory;
            IPC _ipc;
    };
}

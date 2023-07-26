/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** Kitchen
*/

#pragma once
#include <thread>
#include <mutex>
#include <semaphore>
#include <map>
#include <chrono>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Reception.hpp"
#include "../pizza/EnumPizza.hpp"
#include "semaphore.hpp"

namespace plazza {
    class Kitchen {
        public:
            Kitchen(int cooks, int refillTime, float multiplier, int msgqid);
            ~Kitchen();
            void cookRun();
            void launchKitchen();
            void createKitchen();
            void refillIngredients();
            void handleOrder(std::string order);
            bool checkIngredients(Ingredients recipe);
            void removeIngredients(Ingredients recipe);
            void sendStatusToReception();
            std::map<PizzaSize, int> getOrders(PizzaType type);
            std::vector<std::string> splitString(const std::string& input, char delimiter);
            PizzaType getPizzaToCook();
            PizzaType getTypePizza(std::string type);
        private:
            int _cooks;
            int _index;
            bool _canDie;
            int _refillTime;
            int _cookingTime;
            float _multiplier;
            key_t _msgQID;
            std::mutex _mutexIndex;
            std::mutex _mutexStatus;
            std::mutex _mutexOrders;
            std::mutex _mutexActivity;
            std::mutex _mutexIngredients;
            std::thread _refillThread;
            std::vector<std::pair<std::string, std::string>> _cooksStatus;
            std::map<PizzaType, std::map<PizzaSize, int>> _recipes;
            std::map<PizzaType, std::shared_ptr<IPizza>> _pizzas;
            std::map<PizzaType, std::map<PizzaSize, int>> _ordersList;
            std::chrono::steady_clock::time_point _lastActivityTime;
            std::chrono::time_point<std::chrono::system_clock> _end;
            std::chrono::duration<double> _elapsed_seconds;
            std::vector<std::thread> _cooksThreads;
            Factory _factory;
            Semaphore _semaphore;
            Ingredients _ingredients;
            IPC _ipc;
    };
}

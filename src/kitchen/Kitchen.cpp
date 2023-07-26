/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

namespace plazza {
    Kitchen::Kitchen(int cooks, int refillTime, float multiplier, int msgqid): _cooks(cooks), _refillTime(refillTime), _multiplier(multiplier), _msgQID(msgqid)
    {
        _ingredients = {
            .doe = 5,
            .ham = 5,
            .steak = 5,
            .tomato = 5,
            .gruyere = 5,
            .eggplant = 5,
            .mushrooms = 5,
            .chiefLove = 5,
            .goatCheese = 5
        };
        _index = 0;
        _canDie = true;
        _lastActivityTime = std::chrono::steady_clock::now();
        createKitchen();
    }

    Kitchen::~Kitchen()
    {
    }

    void Kitchen::refillIngredients()
    {
        while (42) {
            std::this_thread::sleep_for(std::chrono::milliseconds(_refillTime));
            _mutexIngredients.lock();
            this->_ingredients.doe += 1;
            this->_ingredients.ham += 1;
            this->_ingredients.steak += 1;
            this->_ingredients.tomato += 1;
            this->_ingredients.gruyere += 1;
            this->_ingredients.eggplant += 1;
            this->_ingredients.mushrooms += 1;
            this->_ingredients.chiefLove += 1;
            this->_ingredients.goatCheese += 1;
            _mutexIngredients.unlock();
        }
    }

    std::map<PizzaSize, int> Kitchen::getOrders(PizzaType type)
    {
        std::map<PizzaSize, int> orders;
        if (_ordersList[type][S] > 0)
            orders[S] = _ordersList[type][S];
        if (_ordersList[type][M] > 0)
            orders[M] = _ordersList[type][M];
        if (_ordersList[type][L] > 0)
            orders[L] = _ordersList[type][L];
        if (_ordersList[type][XL] > 0)
            orders[XL] = _ordersList[type][XL];
        if (_ordersList[type][XXL] > 0)
            orders[XXL] = _ordersList[type][XXL];
        return orders;
    }

    PizzaType Kitchen::getTypePizza(std::string type)
    {
        if (type == "regina")
            return PizzaType::Regina;
        if (type == "margarita")
            return PizzaType::Margarita;
        if (type == "americana")
            return PizzaType::Americana;
        if (type == "fantasia")
            return PizzaType::Fantasia;
        return PizzaType::Regina;
    }

    std::vector<std::string> Kitchen::splitString(const std::string& input, char delimiter) {
        std::string token;
        std::istringstream iss(input);
        std::vector<std::string> result;
        while (std::getline(iss, token, delimiter))
            result.push_back(token);
        return result;
    }

    void Kitchen::sendStatusToReception() {
        int i = 0;
        Message message;
        message.mtype = 5;
        message.mtext[0] = '\0';
        std::string status;
        {
            std::lock_guard<std::mutex> lock(_mutexIngredients);
            status = "Ingredients:\n\t\tDoe: " + std::to_string(_ingredients.doe) + "\n\t\tHam: " + std::to_string(_ingredients.ham) + "\n\t\tSteak: " + std::to_string(_ingredients.steak) + "\n\t\tTomato: " + std::to_string(_ingredients.tomato) + "\n\t\tGruyere: " + std::to_string(_ingredients.gruyere) + "\n\t\tEggplant: " + std::to_string(_ingredients.eggplant) + "\n\t\tMushrooms: " + std::to_string(_ingredients.mushrooms) + "\n\t\tChiefLove: " + std::to_string(_ingredients.chiefLove) + "\n\t\tGoatCheese: " + std::to_string(_ingredients.goatCheese) + "\n";
        }
        for (auto &cook : _cooksStatus) {
            status += "\t\tCook " + std::to_string(++i) + " " + cook.first + " " + cook.second + "\n";
        }
        std::strncpy(message.mtext, status.c_str(), sizeof(message.mtext));
        _ipc.sendMessage(_msgQID, message);
    }

    void Kitchen::handleOrder(std::string order)
    {
        Message message;
        message.mtype = 2;
        message.mtext[0] = '\0';
        std::string response = std::string("KO");
        if (order == "status")
            sendStatusToReception();
        PizzaType type = getTypePizza(order);
        if (checkIngredients(_pizzas[type]->getIngredients())) {
            response = std::string("OK");
            {
                std::lock_guard<std::mutex> lock(_mutexOrders);
                _pizzas[type]->addQuantity(1);
            }
        }
        std::strncpy(message.mtext, response.c_str(), sizeof(message.mtext));
        _ipc.sendMessage(_msgQID, message);
    }

    bool Kitchen::checkIngredients(Ingredients recipe)
    {
        return (recipe.doe <= _ingredients.doe
            && recipe.ham <= _ingredients.ham
            && recipe.steak <= _ingredients.steak
            && recipe.tomato <= _ingredients.tomato
            && recipe.gruyere <= _ingredients.gruyere
            && recipe.eggplant <= _ingredients.eggplant
            && recipe.mushrooms <= _ingredients.mushrooms
            && recipe.chiefLove <= _ingredients.chiefLove
            && recipe.goatCheese <= _ingredients.goatCheese);
    }

    void Kitchen::removeIngredients(Ingredients recipe)
    {
        _ingredients.doe -= recipe.doe;
        _ingredients.ham -= recipe.ham;
        _ingredients.steak -= recipe.steak;
        _ingredients.tomato -= recipe.tomato;
        _ingredients.gruyere -= recipe.gruyere;
        _ingredients.eggplant -= recipe.eggplant;
        _ingredients.mushrooms -= recipe.mushrooms;
        _ingredients.chiefLove -= recipe.chiefLove;
        _ingredients.goatCheese -= recipe.goatCheese;
    }

    PizzaType Kitchen::getPizzaToCook()
    {
        for (auto &pizza : _pizzas) {
            if (pizza.second->getQuantity() > 0) {
                pizza.second->removeQuantity(1);
                return pizza.first;
            }
        }
        return PizzaType::None;
    }

    void Kitchen::cookRun()
    {
        int index = 0;
        PizzaType pizzaToCook = PizzaType::None;
        {
            std::lock_guard<std::mutex> lock(_mutexIndex);
            index = _index;
            _index++;
        }
        while (42) {
            pizzaToCook = PizzaType::None;
            {
                std::lock_guard<std::mutex> lock(_mutexStatus);
                _cooksStatus[index] = std::make_pair("idle", "");
            }
            {
                std::lock_guard<std::mutex> lock(_mutexOrders);
                pizzaToCook = getPizzaToCook();
            }
            Message message;
            message.mtype = 3;
            message.mtext[0] = '\0';
            if (pizzaToCook == PizzaType::None) continue;
            Ingredients recipe = _pizzas[pizzaToCook]->getIngredients();
            {
                std::lock_guard<std::mutex> lock(_mutexActivity);
                _lastActivityTime = std::chrono::steady_clock::now();
                _canDie = false;
            }
            _mutexIngredients.lock();
            if (checkIngredients(recipe)) {
                removeIngredients(recipe);
                _mutexIngredients.unlock();
                {
                    std::lock_guard<std::mutex> lock(_mutexStatus);
                    _cooksStatus[index] = std::make_pair("cooking", _pizzas[pizzaToCook]->getName());
                }
                std::chrono::duration<float> cookTime(_pizzas[pizzaToCook]->getCookTime() * _multiplier);
                std::this_thread::sleep_for(cookTime);
                std::string pizzaName = _pizzas[pizzaToCook]->getName();
                std::strncpy(message.mtext, pizzaName.c_str(), sizeof(message.mtext));
                _ipc.sendMessage(_msgQID, message);
                {
                    std::lock_guard<std::mutex> lock(_mutexActivity);
                    _canDie = true;
                    _lastActivityTime = std::chrono::steady_clock::now();
                }
            }
            else {
                _mutexIngredients.unlock();
                {
                    std::lock_guard<std::mutex> lock(_mutexStatus);
                    _pizzas[pizzaToCook]->addQuantity(1);
                }
            }
        }
    }

    void Kitchen::launchKitchen() {
        while (1) {
            std::string order = _ipc.receiveMessage(_msgQID, 1);
            if (order != "KO") handleOrder(order);
            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - _lastActivityTime).count() > 5 && _canDie) {
                break;
            }
        }
        _ipc.destroyChannel(_msgQID);
        exit(0);
    }

    void Kitchen::createKitchen() {
        _pizzas = {
            {PizzaType::Regina, _factory.createPizza(PizzaType::Regina)},
            {PizzaType::Margarita, _factory.createPizza(PizzaType::Margarita)},
            {PizzaType::Americana, _factory.createPizza(PizzaType::Americana)},
            {PizzaType::Fantasia, _factory.createPizza(PizzaType::Fantasia)}
        };
        for (int i = 0; i < _cooks; i++) {
            std::lock_guard<std::mutex> lock(_mutexStatus);
            _cooksStatus.push_back(std::make_pair("idle", ""));
        }
        _refillThread = std::thread(&Kitchen::refillIngredients, this);
        for (int i = 0; i < _cooks; i++)
            _cooksThreads.push_back(std::thread(&Kitchen::cookRun, this));
        launchKitchen();
        if (_refillThread.joinable())
            _refillThread.join();
        for (auto& thread : _cooksThreads) {
            if (thread.joinable())
                thread.join();
        }
    }
}

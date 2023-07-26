/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** Reception
*/

#include "Reception.hpp"

namespace plazza {
    Reception::Reception(float multiplier, int cooksPerKitchen, int replaceIngredientsTime) {
        _ordersList = {
            {PizzaType::Regina, {
                {PizzaSize::S, 0},
                {PizzaSize::M, 0},
                {PizzaSize::L, 0},
                {PizzaSize::XL, 0},
                {PizzaSize::XXL, 0}
            }},
            {PizzaType::Margarita, {
                {PizzaSize::S, 0},
                {PizzaSize::M, 0},
                {PizzaSize::L, 0},
                {PizzaSize::XL, 0},
                {PizzaSize::XXL, 0}
            }},
            {PizzaType::Americana, {
                {PizzaSize::S, 0},
                {PizzaSize::M, 0},
                {PizzaSize::L, 0},
                {PizzaSize::XL, 0},
                {PizzaSize::XXL, 0}
            }},
            {PizzaType::Fantasia, {
                {PizzaSize::S, 0},
                {PizzaSize::M, 0},
                {PizzaSize::L, 0},
                {PizzaSize::XL, 0},
                {PizzaSize::XXL, 0}
            }}
        };
        _pizzas = {
            {PizzaType::Regina, _factory.createPizza(PizzaType::Regina)},
            {PizzaType::Margarita, _factory.createPizza(PizzaType::Margarita)},
            {PizzaType::Americana, _factory.createPizza(PizzaType::Americana)},
            {PizzaType::Fantasia, _factory.createPizza(PizzaType::Fantasia)}
        };
        _multiplier = multiplier;
        _cooksPerKitchen = cooksPerKitchen;
        _replaceIngredientsTime = replaceIngredientsTime;
        _index = 0;
        _indexCommand = 0;
        _kitchenList = {};
        _availableKitchens = 0;
    }

    void Reception::launchShell() {
        std::string getInput;

        while (true) {
            fd_set readfds;
            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;
            FD_ZERO(&readfds);
            FD_SET(0, &readfds);
            if (select(1, &readfds, nullptr, nullptr, &timeout) == -1) break;
            if (FD_ISSET(0, &readfds)) {
                std::getline(std::cin, getInput);
                if (getInput == "status") {
                    printStatus();
                    continue;
                }
                if (getInput == "exit")
                    break;
                if (!getOrder(getInput)) {
                    shouldCreateKitchens();
                    sendOrder();
                }
            }
            handleMessageFromKitchens();
        }
    }

    void Reception::setToZero() {
        for (auto &pizza : _pizzas) {
            pizza.second->setToZero();
        }
    }

    void Reception::checkCommands() {
        _index = 0;
        for (auto &command : _pizzaCommands) {
            if (command[PizzaType::Regina] <= 0 && command[PizzaType::Margarita] <= 0 &&
                command[PizzaType::Americana] <= 0 && command[PizzaType::Fantasia] <= 0) {
                _pizzaCommands.erase(std::remove(_pizzaCommands.begin(), _pizzaCommands.end(), command), _pizzaCommands.end());
                _indexCommand--;
                std::cout << "This order is ready : " << std::endl;
                for (auto &command : _commands[_index]) {
                    std::cout << "\t" << command << std::endl;
                }
                _commands.erase(std::remove(_commands.begin(), _commands.end(), _commands[_index]), _commands.end());
                break;
            }
            _index++;
        }
    }

    void Reception::removeFromCommand(PizzaType type) {
        for (auto &command : _pizzaCommands) {
            if (command[type] > 0)
                command[type] -= 1;
            else
                continue;
        }
        checkCommands();
    }

    void Reception::printOrders() {
        for (auto &command : _pizzaCommands) {
            std::cout << "Order : " << std::endl;
            for (auto &pizza : command) {
                if (pizza.second > 0)
                    std::cout << "\t" << getTypePizzaFromType(pizza.first) << " : " << pizza.second << std::endl;
            }
        }
    }

    int Reception::calculateNumberOfKitchens(int numberOfCooks, int givenNumberOfPizzas) {
        int numberOfKitchens = ceil(static_cast<double>(givenNumberOfPizzas) / numberOfCooks);
        return numberOfKitchens;
    }

    int Reception::getNbKitchenToCreate() {
        int numberOfCooks = _cooksPerKitchen;
        int givenNumberOfPizzas = getNumberPizza( _pizzaCommands[_indexCommand]);
        int numberOfKitchens = calculateNumberOfKitchens(numberOfCooks, givenNumberOfPizzas);
        return numberOfKitchens;
    }

    int Reception::shouldCreateKitchens() {
        int allKitchen = getNbKitchenToCreate();
        _nbOfPizzaPerKitchen = allKitchen;
        if (_availableKitchens > allKitchen) return 1;
        for (int i = 0; i < allKitchen; i++) {
            int id = _ipc.createChannel();
            pid_t pid = fork();
            if (pid == 0) {
                Kitchen kitchen(_cooksPerKitchen, _replaceIngredientsTime, _multiplier, id);
                exit(0);
            }
            _kitchenList.push_back(id);
            _availableKitchens++;
        }
        return 0;
    }

    PizzaType Reception::getPizzaToCook() {
        for (auto &pizza : _pizzaCommands[_indexCommand]) {
            if (pizza.second > 0)
                return pizza.first;
        }
        return PizzaType::None;
    }

    std::vector<std::string> Reception::splitString(const std::string& input, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(input);
        std::string token;
        while (std::getline(iss, token, delimiter))
            result.push_back(token);
        return result;
    }


    void Reception::handleMessageFromKitchens() {
        if (_kitchenList.empty())
            return;
        for (long unsigned int i = 0; i < _kitchenList.size(); i++) {
            std::string messageReceived = _ipc.receiveMessage(_kitchenList[i], 3);
            if (messageReceived != "KO" && getTypePizzaFromString(messageReceived) != PizzaType::None) {
                PizzaType type = getTypePizzaFromString(messageReceived);
                removeFromCommand(type);
            }
            if (messageReceived == "DEAD") {
                _kitchenList.erase(std::remove(_kitchenList.begin(), _kitchenList.end(), _kitchenList[i]), _kitchenList.end());
                _availableKitchens--;
                i--;
                continue;
            }
        }
    }

    void Reception::sendPizzaToKitchen(PizzaType type) {
        Message message;
        message.mtype = 1;
        message.mtext[0] = '\0';
        std::string pizza = getTypePizzaFromType(type);
        std::strncpy(message.mtext, pizza.c_str(), sizeof(message.mtext) - 1);
        message.mtext[sizeof(message.mtext) - 1] = '\0';
        for (long unsigned int i = 0; i < _kitchenList.size(); i++) {
            _ipc.sendMessage(_kitchenList[i], message);
            std::string messageReceived = _ipc.awaitReceiveMessage(_kitchenList[i], 2);
            if (messageReceived == "OK")
                break;
            if (messageReceived == "DEAD") {
                _kitchenList.erase(std::remove(_kitchenList.begin(), _kitchenList.end(), _kitchenList[i]), _kitchenList.end());
                _availableKitchens--;
                i--;
                continue;
            }
        }
    }

    void Reception::sendOrder() {
        std::string messageText = getMessageToSend();
        std::map<PizzaType, int> order;

        std::vector<std::string> orderSplitted = splitString(messageText, ' ');
        for (auto &pizza : orderSplitted) {
            std::vector<std::string> pizzaSplitted = splitString(pizza, '_');
            PizzaType type = getTypePizzaFromString(pizzaSplitted[0]);
            order[type] += (std::stoi(pizzaSplitted[1]));
        }

        for (auto &pizza : order) {
            int numberOfPizza = pizza.second;
            for (int i = 0; i < numberOfPizza; i++) {
                sendPizzaToKitchen(pizza.first);
            }
        }
    }

    std::string Reception::getMessageToSend()
    {
        std::string message;
        if (_pizzaCommands[_indexCommand].empty())
            return "";
        if (_pizzaCommands[_indexCommand][PizzaType::Regina] > 0) {
            message += "regina_";
            message += std::to_string(_pizzaCommands[_indexCommand][PizzaType::Regina]);
            message += " ";
        }
        if (_pizzaCommands[_indexCommand][PizzaType::Margarita] > 0) {
            message += "margarita_";
            message += std::to_string(_pizzaCommands[_indexCommand][PizzaType::Margarita]);
            message += " ";
        }
        if (_pizzaCommands[_indexCommand][PizzaType::Americana] > 0) {
            message += "americana_";
            message += std::to_string(_pizzaCommands[_indexCommand][PizzaType::Americana]);
            message += " ";
        }
        if (_pizzaCommands[_indexCommand][PizzaType::Fantasia] > 0) {
            message += "fantasia_";
            message += std::to_string(_pizzaCommands[_indexCommand][PizzaType::Fantasia]);
            message += " ";
        }
        _indexCommand++;
        return message;
    }

    void Reception::printStatus() {
        std::cout << "Kitchens status:" << std::endl;
        for (auto &kitchen : _kitchenList) {
            _ipc.sendMessage(kitchen, Message{1, "status"});
            std::string message = _ipc.awaitReceiveMessage(kitchen, 5);
            if (message != "KO") {
                std::cout << "\tKitchen " << kitchen << ":" << std::endl;
                std::cout << message << std::endl;
                continue;
            }
            if (message == "DEAD") {
                _kitchenList.erase(std::remove(_kitchenList.begin(), _kitchenList.end(), kitchen), _kitchenList.end());
                _availableKitchens--;
            }
        }
    }

    std::map<PizzaType, int> Reception::addCommand() {
        std::map<PizzaType, int> command;
        for (auto &pizza : _pizzas) {
            if (pizza.second->getQuantity() > 0) {
                command[pizza.first] = pizza.second->getQuantity();
                pizza.second->setToZero();
            }
        }
        return command;
    }

    int Reception::getOrder(std::string getInput) {
        std::regex pattern("([a-zA-Z]+) (S|M|L|XL|XXL) (x[1-9][0-9]*)");
        std::sregex_iterator iter(getInput.begin(), getInput.end(), pattern);
        std::sregex_iterator end;
        if (iter == end) {
            std::cout << "Error: Invalid input." << " For example : margarita S x3" << std::endl;
            return 1;
        }
        _tempVector.clear();
        while (iter != end) {
            std::smatch match = *iter;
            _tempString.clear();
            if (listOrder(match[1], match[2], std::stoi(match[3].str().substr(1))))
                return 1;
            _tempVector.push_back(_tempString);
            ++iter;
        }
        _commands.push_back(_tempVector);
        _pizzaCommands.push_back(addCommand());
        return 0;
    }

    void Reception::printOrdersList() {
        for (auto &i : _ordersList) {
            std::cout << "Pizza: " << getTypePizzaFromType(i.first) << std::endl;
            for (auto &j : i.second) {
                std::cout << "Size: " << getSizePizza(j.first) << " Number: " << j.second << std::endl;
            }
        }
    }

    std::string Reception::getSizePizza(PizzaSize size) {
        if (size == PizzaSize::S)
            return "S";
        else if (size == PizzaSize::M)
            return "M";
        else if (size == PizzaSize::L)
            return "L";
        else if (size == PizzaSize::XL)
            return "XL";
        else if (size == PizzaSize::XXL)
            return "XXL";
        else
            return "ERROR";
    }

    std::string Reception::getTypePizzaFromType(PizzaType type) {
        if (type == PizzaType::Regina)
            return "regina";
        else if (type == PizzaType::Margarita)
            return "margarita";
        else if (type == PizzaType::Americana)
            return "americana";
        else if (type == PizzaType::Fantasia)
            return "fantasia";
        else
            return "ERROR";
    }

    PizzaType Reception::getTypePizzaFromString(std::string name) {
        if (name == "regina")
            return PizzaType::Regina;
        else if (name == "margarita")
            return PizzaType::Margarita;
        else if (name == "americana")
            return PizzaType::Americana;
        else if (name == "fantasia")
            return PizzaType::Fantasia;
        else
            return PizzaType::None;
    }

    void Reception::printPizza(PizzaType pizza) {
        std::cout << "Pizza: " << getTypePizzaFromType(pizza) << std::endl;
        for (auto &i : _ordersList[pizza]) {
            if (i.second == 0)
                continue;
            std::cout << "Size: " << getSizePizza(i.first) << " Number: " << i.second << std::endl;
        }
    }

    int Reception::getNumberPizza(std::map<PizzaType, int> pizza) {
        int i = 0;
        for (auto &j : pizza) {
            i += j.second;
        }
        return i;
    }

    int Reception::listOrder(std::string order, std::string size, int number) {
        PizzaType pizzaType;
        if (order == "regina")
            pizzaType = PizzaType::Regina;
        else if (order == "margarita")
            pizzaType = PizzaType::Margarita;
        else if (order == "americana")
            pizzaType = PizzaType::Americana;
        else if (order == "fantasia")
            pizzaType = PizzaType::Fantasia;
        else {
            std::cout << "Unknown order: " << order << ". The possible choices are: Regina, Margarita, Americana, Fantasia" << std::endl;
            return 1;
        }
        if (size == "S")
            _ordersList[pizzaType][PizzaSize::S] += number;
        else if (size == "M")
            _ordersList[pizzaType][PizzaSize::M] += number;
        else if (size == "L")
            _ordersList[pizzaType][PizzaSize::L] += number;
        else if (size == "XL")
            _ordersList[pizzaType][PizzaSize::XL] += number;
        else if (size == "XXL")
            _ordersList[pizzaType][PizzaSize::XXL] += number;
        else {
            std::cout << "Unknown Size: " << size << ". The possible choices are: S, M, L, XL, XXL" << std::endl;
            return 1;
        }
        _tempString = order + " " + std::to_string(number) + "x " + "size=" + size;
        _pizzas[pizzaType]->addQuantity(number);
        return 0;
    }

    void takingOrder() {
    }


}

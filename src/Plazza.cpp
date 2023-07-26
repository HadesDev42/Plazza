/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** main
*/

#include <memory>
#include "exceptions/KitchenExceptions.hpp"
#include "reception/Reception.hpp"

int main(int ac, char **av) {
    try {
        if (ac != 4)
            throw plazza::KitchenExceptions("USAGE: ./plazza [multiplier] [cooks_per_kitchen] [replace_ingredients_time]");
        if (std::atof(av[1]) < 0 || std::atoi(av[2]) < 0 || std::atoi(av[3]) < 0)
            throw plazza::KitchenExceptions("All parameters must be positive values");
        std::unique_ptr<plazza::Reception> reception = std::make_unique<plazza::Reception>(std::atof(av[1]), std::atoi(av[2]), std::atoi(av[3]));
        reception->launchShell();
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}

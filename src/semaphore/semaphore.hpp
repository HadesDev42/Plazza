/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** semaphore
*/

#pragma once

#include <semaphore.h>

namespace plazza
{
    class Semaphore {
        public:
            Semaphore();
            Semaphore(int value);
            ~Semaphore();
            void wait();
            void post();
        private:
            sem_t _sem;
    };
}

/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** semaphore
*/

#include "semaphore.hpp"

namespace plazza
{
    Semaphore::Semaphore()
    {
        sem_init(&_sem, 0, 0);
    }

    Semaphore::Semaphore(int value)
    {
        sem_init(&_sem, 0, value);
    }

    Semaphore::~Semaphore()
    {
        sem_destroy(&_sem);
    }

    void Semaphore::wait()
    {
        sem_wait(&_sem);
    }

    void Semaphore::post()
    {
        sem_post(&_sem);
    }
}

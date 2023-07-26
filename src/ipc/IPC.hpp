/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** IPC
*/

#ifndef IPC_HPP_
#define IPC_HPP_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include <string>

namespace plazza {
    struct Message {
        long mtype;
        char mtext[2048];
    };

    class IPC {
        public:
            IPC();
            ~IPC();
            int createChannel();
            void destroyChannel(int id);
            int sendMessage(int id, Message message);
            std::string receiveMessage(int id, int type);
            std::string awaitReceiveMessage(int id, int type);
        protected:
        private:
    };
}

#endif /* !IPC_HPP_ */

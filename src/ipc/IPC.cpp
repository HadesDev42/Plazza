/*
** EPITECH PROJECT, 2023
** B-CCP-400-MPL-4-1-theplazza-thibault.bernuz
** File description:
** IPC
*/

#include "IPC.hpp"
#include "Reception.hpp"

namespace plazza {
    IPC::IPC() {
    }

    IPC::~IPC() {
    }

    int IPC::sendMessage(int id, Message message) {
        if (msgsnd(id, &message, sizeof(message), 0) == -1) {
            if (errno == EIDRM || errno == ENOENT) {
                std::cerr << "Error: msgsnd" << std::endl;
                return -1;
            }
            return 1;
        }
        return 0;
    }

    std::string IPC::awaitReceiveMessage(int id, int type) {
        Message message;
        if (msgrcv(id, &message, sizeof(message), type, 0) == -1) {
            if (errno == EIDRM || errno == ENOENT) {
                return "DEAD";
            }
            return "KO";
        }

        return message.mtext;
    }

    std::string IPC::receiveMessage(int id, int type) {
        Message message;
        if (msgrcv(id, &message, sizeof(message), type, IPC_NOWAIT) == -1) {
            if (errno == EIDRM || errno == ENOENT) {
                return "DEAD";
            }
            return "KO";
        }
        return message.mtext;
    }

    void IPC::destroyChannel(int id) {
        if (msgctl(id, IPC_RMID, NULL) == -1) {
            std::cerr << "Error: msgctl" << std::endl;
            return;
        }
    }

    int IPC::createChannel() {
        int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
        if (msgid == -1) {
            std::cerr << "Error: msgget" << std::endl;
            return 0;
        }
        return msgid;
    }
}

#pragma once

#include "IService.hpp"
#include "UserRepository.hpp"
#include "ActionRepository.hpp"

class ServerService : public IService
{
    UserRepository* users = nullptr;
    ActionRepository* actions = nullptr;

    QMap<QTcpSocket*, qint32> loggedClients{ };

public:
    explicit ServerService(UserRepository* users, ActionRepository* actions) : IService(), users{ users }, actions{ actions } { }

    void login(const User& user, QTcpSocket* client) override;
    void logout(const User& user, QTcpSocket* client) override;
    void takeAction(const Process& process, QTcpSocket* client) override;
};
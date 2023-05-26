#pragma once

#include "../domain/User.hpp"
#include "../domain/Process.hpp"
#include <qtcpsocket.h>

class IService
{
public:
    virtual ~IService() { };

    virtual void login(const User& user, QTcpSocket* client) = 0;
    virtual void logout(const User& user, QTcpSocket* client) = 0;
    virtual void takeAction(const Process& process, QTcpSocket* client) = 0;
};
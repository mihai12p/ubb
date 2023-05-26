#include "ServerService.hpp"

void ServerService::login(const User& user, QTcpSocket* client)
{
    qint32 uid = this->users->isValidUser(user.getUsername(), user.getPassword());
    if (!uid)
    {
        throw std::exception("Authentication failed.");
    }

    for (QTcpSocket* clientSocket : this->loggedClients.keys())
    {
        if (this->loggedClients.value(clientSocket) == uid)
        {
            throw std::exception("User already logged in.");
        }
    }

    this->loggedClients[client] = uid;
}

void ServerService::logout(const User& user, QTcpSocket* client)
{
    if (!this->loggedClients.contains(client))
    {
        throw std::exception("User is not logged in.");
    }

    this->loggedClients.remove(client);
}

void ServerService::takeAction(const Process& process, QTcpSocket* client)
{
    if (!process.getName().endsWith("otepad.exe"))
    {
        throw std::exception("Actions are not permitted on this process.");
    }

    this->actions->save(process);
}
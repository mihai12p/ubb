#pragma once

#include "ClientWorker.hpp"

class ClientController : public QObject
{
    Q_OBJECT

public:
    ClientController(ClientWorker& worker, QObject* parent = nullptr) : QObject(parent), worker{ worker } { }

    const ClientWorker& GetWorker() const { return this->worker; }

    void login(const QString& username, const QString& password);
    void logout();
    QList<Process> scanComputer();
    QList<QString> getProcessDetails(qint32 PID);
    void takeAction(Process& selectedProcess, int action);

    const User& getUser() const
    {
        return this->currentUser;
    }

private:
    ClientWorker& worker;
    User currentUser{ };
};
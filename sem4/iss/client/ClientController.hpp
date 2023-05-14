#pragma once

#include "ClientWorker.hpp"

class ClientController : public QObject
{
    Q_OBJECT

public:
    ClientController(ClientWorker& worker, QObject* parent = nullptr) : QObject(parent), worker{ worker } { }

    const QTcpSocket& GetSocket() const { return this->worker.GetSocket(); }

    void Login(const QString& username, const QString& password);

private:
    ClientWorker& worker;
};
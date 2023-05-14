#include "ClientController.hpp"
#include "../domain/User.hpp"

void ClientController::Login(const QString& username, const QString& password)
{
    User user(5, username, password);
    this->worker.Login(user);
    qInfo() << "Login succeeded...";
}
#include "ClientController.hpp"
#include "../domain/User.hpp"

void ClientController::login(const QString& username, const QString& password)
{
    User user(username, password);
    this->worker.login(user, this->worker.GetTcpSocket());
    this->currentUser = user;
}

void ClientController::logout()
{
    qInfo() << "Controller logout...";
    this->worker.logout(this->currentUser, this->worker.GetTcpSocket());
}

QList<Process> ClientController::scanComputer()
{
    qInfo() << "Scanning computer...";
    return this->worker.scanComputer();
}

QList<QString> ClientController::getProcessDetails(qint32 PID)
{
    qInfo() << "Getting details for process with ID" << PID;
    return this->worker.getProcessDetails(PID);
}

void ClientController::takeAction(Process& selectedProcess, int action)
{
    if (!selectedProcess.getPID())
    {
        return;
    }

    QString actionString{ };
    switch (action)
    {
    case 0:
        actionString = "Suspending";
        break;
    case 1:
        actionString = "Resuming";
        break;
    case 2:
        actionString = "Killing";
        break;
    default:
        actionString = "None";
        break;
    }

    qInfo() << actionString << selectedProcess.getName() << "...";
    selectedProcess.setAction(action);
    this->worker.takeAction(selectedProcess, this->worker.GetTcpSocket());
}
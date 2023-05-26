#include "ServerWorker.hpp"
#include <QtCore/qthread.h>
#include "../client/ClientWorker.hpp"

ServerWorker::ServerWorker(quint16 port, IService* service, QObject* parent) : QObject(parent), service{ service }
{
    this->block = { 0 };
    this->outputStream.setVersion(QDataStream::Qt_6_5);

    if (!this->server.listen(QHostAddress::Any, port))
    {
        qCritical() << "Unable to start the server " << this->server.errorString();
        return;
    }

    connect(&this->server, &QTcpServer::newConnection, this, &ServerWorker::OnConnect);
    qInfo() << "Server started.\nWaiting for clients...";
}

ServerWorker::~ServerWorker()
{
    if (this->server.isListening())
    {
        disconnect(&this->server, &QTcpServer::newConnection, 0, 0);
    }

    this->server.close();
}

void ServerWorker::OnConnect()
{
    while (this->server.hasPendingConnections())
    {
        QTcpSocket* clientSocket = this->server.nextPendingConnection();
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ServerWorker::OnDisconnect);
        connect(clientSocket, &QTcpSocket::readyRead, this, &ServerWorker::OnRead);
        qInfo() << "A client has connected." << clientSocket->socketDescriptor();
    }
}

void ServerWorker::OnDisconnect()
{
    QTcpSocket* clientSocket = reinterpret_cast<QTcpSocket*>(this->sender());

    this->connections.removeOne(clientSocket);
    this->service->logout(User(), clientSocket);
    qInfo() << "A client has disconnected." << clientSocket;
}

void ServerWorker::OnRead()
{
    QTcpSocket* clientSocket = reinterpret_cast<QTcpSocket*>(this->sender());

    QByteArray block = { 0 };
    QDataStream inputStream(&block, QIODevice::ReadOnly);
    inputStream.setDevice(clientSocket);
    inputStream.setVersion(QDataStream::Qt_6_5);

    this->HandleRequest(inputStream, clientSocket);
}

void ServerWorker::HandleRequest(QDataStream& inputStream, QTcpSocket* clientSocket)
{
    IResponse* response = nullptr;

    inputStream.startTransaction();

    RequestType requestType;
    inputStream >> requestType;

    if (requestType == RequestType::LOGIN)
    {
        User user{ };
        inputStream >> user;

        try
        {
            this->service->login(user, clientSocket);
            this->connections.append(clientSocket);

            response = new Response(ResponseType::OK, QString(""));
        }
        catch (const std::exception e)
        {
            response = new Response(ResponseType::ERROR, QString(e.what()));
        }
    }
    else if (requestType == RequestType::LOGOUT)
    {
        User user{ };
        inputStream >> user;

        try
        {
            this->service->logout(user, clientSocket);
            response = new Response(ResponseType::OK, QString(""));
        }
        catch (const std::exception e)
        {
            response = new Response(ResponseType::ERROR, QString(e.what()));
        }
    }
    else if (requestType == RequestType::TAKE_ACTION)
    {
        Process selectedProcess{ };
        inputStream >> selectedProcess;

        try
        {
            this->service->takeAction(selectedProcess, clientSocket);
            response = new Response(ResponseType::OK, QString(""));
            response->SetAdditionalData(selectedProcess);

            this->NotifyOthers(clientSocket, requestType, response);
        }
        catch (const std::exception e)
        {
            response = new Response(ResponseType::DENY, QString(e.what()));
        }
    }

    if (inputStream.commitTransaction())
    {
        this->SendResponse<QString>(clientSocket, requestType, response);
    }

    if (response)
    {
        delete response;
    }
}

void ServerWorker::NotifyOthers(QTcpSocket* sender, RequestType requestType, IResponse* response)
{
    for (QTcpSocket* clientSocket : this->connections)
    {
        if (clientSocket != sender)
        {
            this->SendResponse<QString>(clientSocket, requestType, response);
        }
    }
}
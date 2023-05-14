#include "ServerWorker.hpp"
#include <QtCore/qthread.h>

ServerWorker::ServerWorker(QObject* parent) : QObject(parent)
{
    this->block = { 0 };
    this->outputStream.setVersion(QDataStream::Qt_6_5);

    if (!this->server.listen(QHostAddress::Any, 55002))
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

        for (QTcpSocket* clientSocket : this->connections)
        {
            //Response response(ResponseType::OK, static_cast<qint16>(0));
            //this->SendResponse(clientSocket, response);
        }
    }

    this->server.close();
}

void ServerWorker::OnConnect()
{
    while (this->server.hasPendingConnections())
    {
        QTcpSocket* clientSocket = this->server.nextPendingConnection();
        this->connections.insert(clientSocket);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ServerWorker::OnDisconnect);
        connect(clientSocket, &QTcpSocket::readyRead, this, &ServerWorker::OnRead);
        qInfo() << "A client has connected." << clientSocket->socketDescriptor();
    }
}

void ServerWorker::OnDisconnect()
{
    QTcpSocket* clientSocket = reinterpret_cast<QTcpSocket*>(sender());

    this->connections.remove(clientSocket);
    qInfo() << "A client has disconnected." << clientSocket->socketDescriptor();
}

void ServerWorker::OnRead()
{
    QTcpSocket* clientSocket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray block = { 0 };
    QDataStream inputStream(&block, QIODevice::ReadOnly);
    inputStream.setDevice(clientSocket);
    inputStream.setVersion(QDataStream::Qt_6_5);

    this->HandleRequest(inputStream, clientSocket);
}

void ServerWorker::HandleRequest(QDataStream& inputStream, QTcpSocket* clientSocket)
{
    inputStream.startTransaction();

    RequestType requestType;
    inputStream >> requestType;

    if (requestType == RequestType::LOGIN)
    {
        User user{ };
        inputStream >> user;

        qInfo() << "New message from" << clientSocket->socketDescriptor() << ":" << user.getId() << user.getUsername() << user.getPassword();

    }

    if (inputStream.commitTransaction())
    {
        Response response(ResponseType::OK, static_cast<qint16>(0));
        this->SendResponse<qint16>(clientSocket, response);
    }
}
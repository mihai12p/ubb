#pragma once

#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include "Response.hpp"
#include "Request.hpp"
#include "IService.hpp"
#include "../domain/User.hpp"

class ServerWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServerWorker(quint16 port, IService* service, QObject* parent = nullptr);
    ~ServerWorker();

private:
    void HandleRequest(QDataStream& inputStream, QTcpSocket* clientSocket);

    template <typename T>
    qint64 SendResponse(QTcpSocket* clientSocket, RequestType requestType, IResponse* response)
    {
        this->outputStream << requestType << response->getResponseType() << response->GetData();
        if (requestType == RequestType::TAKE_ACTION && response->getResponseType() == ResponseType::OK)
        {
            this->outputStream << response->GetAdditionalData();
        }
        qint64 bytesWritten = clientSocket->write(this->block);
        clientSocket->flush();
        this->block.clear();
        this->outputStream.device()->reset();

        return bytesWritten;
    }

    void NotifyOthers(QTcpSocket* sender, RequestType requestType, IResponse* response);

private slots:
    void OnConnect();
    void OnDisconnect();
    void OnRead();

private:
    QTcpServer server{ };
    QList<QTcpSocket*> connections{ };

    QByteArray block{ };
    QDataStream outputStream{ &block, QIODevice::WriteOnly };

    IService* service = nullptr;
};
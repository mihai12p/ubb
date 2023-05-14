#pragma once

#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include "Response.hpp"
#include "Request.hpp"
#include "../domain/User.hpp"

class ServerWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServerWorker(QObject* parent = nullptr);
    ~ServerWorker();

private:
    void HandleRequest(QDataStream& inputStream, QTcpSocket* clientSocket);

    template<typename T>
    qint64 SendResponse(QTcpSocket* clientSocket, Response<T> response)
    {
        this->outputStream << response.getResponseType() << response.GetData();
        qInfo() << this->block;
        qint64 bytesWritten = clientSocket->write(this->block);
        clientSocket->flush();
        this->block.clear();
        this->outputStream.device()->reset();

        return bytesWritten;
    }

private slots:
    void OnConnect();
    void OnDisconnect();
    void OnRead();

private:
    QTcpServer server{ };
    QSet<QTcpSocket*> connections = { 0 };

    QByteArray block{ };
    QDataStream outputStream{ &block, QIODevice::WriteOnly };
};
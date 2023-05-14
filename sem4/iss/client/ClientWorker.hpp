#pragma once

#include <QtCore/qobject.h>
#include <QtCore/qthread.h>
#include <QtCore/qtimer.h>
#include <QtNetwork/qtcpsocket.h>
#include "../server/Request.hpp"
#include "../server/Response.hpp"
#include "../domain/User.hpp"

class ClientWorker : public QObject
{
    Q_OBJECT

public:
    ClientWorker(const QString& host, int port, QObject* parent = nullptr);

    const QTcpSocket& GetSocket() const { return this->socket; }

    void Login(User& user);

private:
    void InitializeConnection();
    void ResponseReceived();
    void HandleResponse(IResponse* response);

    template<typename T>
    void SendRequest(Request<T> request)
    {
        this->outputStream << request.getRequestType() << request.GetData();
        this->socket.write(this->block);
        this->socket.flush();
        this->block.clear();
        this->outputStream.device()->reset();
    }

signals:
    void responseRead(IResponse* response);

private slots:
    void OnConnect();
    void OnDisconnect();
    void OnTimeout();

private:
    QString host{ };
    int port = 0;

    volatile bool isConnected = true;

    QTcpSocket socket{ this };
    QByteArray block{ };
    QDataStream outputStream{ &block, QIODevice::WriteOnly };
    QTimer timeoutTimer{ };
};
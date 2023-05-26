#pragma once

#include <QtCore/qobject.h>
#include <QtCore/qtimer.h>
#include "../server/Request.hpp"
#include "../server/Response.hpp"
#include "../domain/Scan.hpp"
#include "../domain/ResultsInterpreter.hpp"
#include "../server/IService.hpp"

class ClientWorker : public QObject, public IService
{
    Q_OBJECT

public:
    ClientWorker(const QString& host, int port, QObject* parent = nullptr);

    const QTcpSocket& GetSocket() const { return this->socket; }
    QTcpSocket* GetTcpSocket() { return &this->socket; }
 
    void login(const User& user, QTcpSocket* client) override;
    void logout(const User& user, QTcpSocket* client) override;
    void takeAction(const Process& selectedProcess, QTcpSocket* client) override;
    QList<Process> scanComputer();
    QList<QString> getProcessDetails(qint32 PID);

private:
    void InitializeConnection();
    void ResponseReceived();
    void HandleResponse(RequestType requestType, IResponse* response);

    template <typename T>
    void SendRequest(Request<T> request)
    {
        this->outputStream << request.getRequestType() << request.GetData();
        this->socket.write(this->block);
        this->socket.flush();
        this->block.clear();
        this->outputStream.device()->reset();
    }

signals:
    void responseRead(RequestType requestType, IResponse* response);
    void errorOccurred(const QString& error);
    void continueLogin();
    void rescanComputer();

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

    QTcpSocket* client = nullptr;
};
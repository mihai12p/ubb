#include "ClientWorker.hpp"

ClientWorker::ClientWorker(const QString& host, int port, QObject* parent) : QObject(parent)
{
    this->host = host;
    this->port = port;

    this->isConnected = false;

    this->outputStream.setVersion(QDataStream::Qt_6_5);

    this->timeoutTimer.setSingleShot(true);
    connect(&this->timeoutTimer, &QTimer::timeout, this, &ClientWorker::OnTimeout);
}

void ClientWorker::OnTimeout()
{
    if (this->socket.state() == QTcpSocket::ConnectingState)
    {
        this->socket.abort();
        emit this->socket.errorOccurred(QTcpSocket::SocketTimeoutError);
    }
}

void ClientWorker::ResponseReceived()
{
    qDebug() << "Hello from thread " << QThread::currentThread();

    QByteArray block = { 0 };
    QDataStream inputStream(&block, QIODevice::ReadOnly);
    inputStream.setDevice(&this->socket);
    inputStream.setVersion(QDataStream::Qt_6_5);

    IResponse* response = nullptr;
    {
        inputStream.startTransaction();

        ResponseType responseType;
        inputStream >> responseType;

        if (responseType == ResponseType::OK)
        {
            qint16 data = 0;
            inputStream >> data;
            response = new Response<decltype(data)>(responseType, data);
        }

        if (response && inputStream.commitTransaction())
        {
            emit responseRead(response);
        }
    }
}

void ClientWorker::OnDisconnect()
{
    this->isConnected = false;
    this->timeoutTimer.stop();

    disconnect(&this->socket, &QTcpSocket::connected, 0, 0);
    disconnect(&this->socket, &QTcpSocket::disconnected, 0, 0);
    disconnect(&this->socket, &QTcpSocket::readyRead, 0, 0);

    switch (this->socket.state())
    {
    case QAbstractSocket::SocketState::UnconnectedState:
        this->socket.disconnectFromHost();
        break;
    default:
        this->socket.abort();
    }
}


void ClientWorker::InitializeConnection()
{
    if (this->isConnected)
    {
        return;
    }

    this->timeoutTimer.start(3000); // 3 seconds

    this->socket.connectToHost(this->host, this->port);
    connect(&this->socket, &QTcpSocket::disconnected, this, &ClientWorker::OnDisconnect);
    connect(&this->socket, &QTcpSocket::connected, this, &ClientWorker::OnConnect);
}

void ClientWorker::OnConnect()
{
    this->isConnected = true;

    connect(&this->socket, &QTcpSocket::readyRead, this, &ClientWorker::ResponseReceived);
    connect(this, &ClientWorker::responseRead, &ClientWorker::HandleResponse);
}

void ClientWorker::HandleResponse(IResponse* response)
{
    if (response->getResponseType() == ResponseType::OK)
    {
        qDebug() << "Hello from YESSSSSSSS " << QThread::currentThread();
    }
    else
    {
        qDebug() << "Hello from NOPE " << QThread::currentThread();
    }

    delete response;
}

void ClientWorker::Login(User& user)
{
    this->InitializeConnection();

    Request request(RequestType::LOGIN, user);
    this->SendRequest<User>(request);
}
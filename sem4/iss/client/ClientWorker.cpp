#include "ClientWorker.hpp"
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

#undef ERROR

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
    QByteArray block = { 0 };
    QDataStream inputStream(&block, QIODevice::ReadOnly);
    inputStream.setDevice(&this->socket);
    inputStream.setVersion(QDataStream::Qt_6_5);

    {
        inputStream.startTransaction();

        RequestType requestType;
        inputStream >> requestType;

        ResponseType responseType;
        inputStream >> responseType;

        QString data{ };
        inputStream >> data;
        IResponse* response = new Response<QString>(responseType, data);

        if (requestType == RequestType::TAKE_ACTION && responseType == ResponseType::OK)
        {
            Process process{ };
            inputStream >> process;
            response->SetAdditionalData(process);
        }

        if (response && inputStream.commitTransaction())
        {
            emit responseRead(requestType, response);
        }
    }
}

void ClientWorker::OnDisconnect()
{
    this->isConnected = false;

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

void ClientWorker::HandleResponse(RequestType requestType, IResponse* response)
{
    if (requestType == RequestType::LOGIN)
    {
        if (response->getResponseType() == ResponseType::OK)
        {
            emit this->continueLogin();
        }
        else if (response->getResponseType() == ResponseType::ERROR)
        {
            this->client = nullptr;
            emit this->errorOccurred(response->GetData());
        }
    }
    else if (requestType == RequestType::LOGOUT)
    {
        if (response->getResponseType() == ResponseType::ERROR)
        {
            emit this->errorOccurred(response->GetData());
        }
    }
    else if (requestType == RequestType::TAKE_ACTION)
    {
        if (response->getResponseType() == ResponseType::OK)
        {
            ResultsInterpreter resultsInterpreter(response->GetAdditionalData());
            resultsInterpreter.TakeAction();
            Sleep(500);
            emit rescanComputer();
        }
        else if (response->getResponseType() == ResponseType::DENY)
        {
            emit this->errorOccurred(response->GetData());
        }
    }

    if (response)
    {
        delete response;
    }
}

void ClientWorker::login(const User& user, QTcpSocket* client)
{
    this->InitializeConnection();

    Request request(RequestType::LOGIN, user);
    this->SendRequest<User>(request);
    this->client = client;
}

void ClientWorker::logout(const User& user, QTcpSocket* client)
{
    Request request(RequestType::LOGOUT, user);
    this->SendRequest<User>(request);
}

QList<Process> ClientWorker::scanComputer()
{
    FullScan scan;
    scan.PerformScan();
    return scan.getResults();
}

QList<QString> ClientWorker::getProcessDetails(qint32 PID)
{
    QList<QString> details{ };

    HANDLE snapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapHandle == INVALID_HANDLE_VALUE)
    {
        emit this->errorOccurred("Invalid snapHandle value");
        return details;
    }

    PROCESSENTRY32W pe32{ };
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(snapHandle, &pe32))
    {
        CloseHandle(snapHandle);
        emit this->errorOccurred("Process32FirstW has failed");
        return details;
    }

    do
    {
        if (pe32.th32ProcessID == PID)
        {
            Process process(pe32.th32ProcessID, pe32.th32ParentProcessID, QString::fromWCharArray(pe32.szExeFile, wcslen(pe32.szExeFile)));
            details = process.getDetails();
            break;
        }
    } while (Process32NextW(snapHandle, &pe32));

    CloseHandle(snapHandle);
    return details;
}

void ClientWorker::takeAction(const Process& selectedProcess, QTcpSocket* client)
{
    Request request(RequestType::TAKE_ACTION, selectedProcess);
    this->SendRequest<Process>(request);
}
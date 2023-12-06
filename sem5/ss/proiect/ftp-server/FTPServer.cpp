#include "pch.h"
#include "FTPServer.hpp"
#include "Utils.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "21"

FTPServer::FTPServer()
{
    this->threadPool = std::make_unique<BS::thread_pool_light>(16);

    WSADATA wsaData = { 0 };
    int status = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (status)
    {
        const std::string& message = "WSAStartup failed with status " + std::to_string(status);
        throw std::exception(message.c_str());
    }
}

FTPServer::~FTPServer()
{
    int status = closesocket(this->listenSocket);
    if (!status)
    {
        const std::string& message = "closesocket failed with status " + std::to_string(WSAGetLastError());
        std::cout << message.c_str() << std::endl;
    }

    status = WSACleanup();
    if (status)
    {
        const std::string& message = "WSACleanup failed with status " + std::to_string(WSAGetLastError());
        std::cout << message.c_str() << std::endl;
    }
}

NTSTATUS
FTPServer::Start()
{
    ADDRINFOA hints = { 0 };
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    //hints.ai_flags = AI_PASSIVE;

    PADDRINFOA result = nullptr;
    int status = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (status)
    {
        std::cout << "getaddrinfo failed with status " << status << std::endl;
        return STATUS_UNSUCCESSFUL;
    }

    this->listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (this->listenSocket == INVALID_SOCKET)
    {
        std::cout << "socket failed with status " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return STATUS_UNSUCCESSFUL;
    }

    status = bind(this->listenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (status == SOCKET_ERROR)
    {
        std::cout << "bind failed with status " << WSAGetLastError() << std::endl;
        freeaddrinfo(result);
        return STATUS_UNSUCCESSFUL;
    }

    freeaddrinfo(result);

    status = listen(this->listenSocket, SOMAXCONN);
    if (status == SOCKET_ERROR)
    {
        std::cout << "listen failed with status " << WSAGetLastError() << std::endl;
        return STATUS_UNSUCCESSFUL;
    }

    std::cout << "Server is ready and listening on port " << DEFAULT_PORT << std::endl;

    this->HandleConnections();

    return STATUS_SUCCESS;
}

VOID
FTPServer::HandleConnections()
{
    while (true)
    {
        SOCKADDR_IN clientInfo = { 0 };
        int clientInfoSize = sizeof(clientInfo);
        SOCKET* clientSocket = new SOCKET(accept(this->listenSocket, reinterpret_cast<PSOCKADDR>(&clientInfo), &clientInfoSize));
        if (*clientSocket == INVALID_SOCKET)
        {
            std::cout << "accept failed with status " << WSAGetLastError() << std::endl;
            delete clientSocket;
        }
        else
        {
            this->threadPool->push_task([&, clientInfo]
                {
                    char clientIP[INET_ADDRSTRLEN] = { 0 };
                    inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);

                    std::cout << "Client connected from IP: " << clientIP << std::endl;

                    CLIENT_CONTEXT clientContext = { .Socket = *clientSocket, .CurrentDir = R"(D:\facultate-repo)", .IPv4 = clientInfo.sin_addr };
                    this->HandleConnection(clientContext);

                    closesocket(*clientSocket);
                    delete clientSocket;
                });
        }
    }
}

VOID
FTPServer::HandleConnection(_Inout_ CLIENT_CONTEXT& ClientContext)
{
    this->SendString(ClientContext, "220 FTP Server Ready\r\n");

    int status = 0;
    do
    {
        char buffer[DEFAULT_BUFLEN] = { 0 };
        int bufferSize = sizeof(buffer);

        status = recv(ClientContext.Socket, buffer, bufferSize, 0);
        std::cout << "Command received: " << buffer;
        if (status > 0)
        {
            std::string command(buffer, status);
            this->ProcessCommand(command, ClientContext);
        }
        else if (!status)
        {
            std::cout << "Connection closing..." << std::endl;
        }
        else
        {
            std::cout << "recv failed: " << WSAGetLastError() << std::endl;
            return;
        }

    } while (status > 0);
}

VOID
FTPServer::ProcessCommand(_In_ const std::string& Command, _Inout_ CLIENT_CONTEXT& ClientContext)
{
    if (!Command.ends_with("\r\n"))
    {
        return;
    }

    const std::string& processedCommand = Command.substr(0, Command.size() - 2);
    const std::string& command = processedCommand.substr(0, processedCommand.find_first_of(" "));
    const std::string& argument = processedCommand.substr(processedCommand.find_first_of(" ") + 1);

    if (!command.compare("USER"))
    {
        this->HandleUSER(ClientContext, argument);
    }
    else if (!command.compare("PASS"))
    {
        this->HandlePASS(ClientContext, argument);
    }
    else if (!command.compare("SYST"))
    {
        this->HandleSYST(ClientContext);
    }
    else if (!command.compare("FEAT"))
    {
        this->HandleFEAT(ClientContext);
    }
    else if (!command.compare("PWD"))
    {
        this->HandlePWD(ClientContext);
    }
    else if (!command.compare("CWD"))
    {
        this->HandleCWD(ClientContext, argument);
    }
    else if (!command.compare("TYPE"))
    {
        this->HandleTYPE(ClientContext, argument);
    }
    else if (!command.compare("LIST"))
    {
        this->HandleLIST(ClientContext, argument);
    }
    else if (!command.compare("PORT"))
    {
        this->HandlePORT(ClientContext, argument);
    }
    else if (!command.compare("REST"))
    {
        this->HandleREST(ClientContext, argument);
    }
    else if (!command.compare("QUIT"))
    {
        this->HandleQUIT(ClientContext, argument);
    }
    else if (!command.compare("RETR"))
    {
        this->HandleRETR(ClientContext, argument);
    }
    else if (!command.compare("STOR"))
    {
        this->HandleSTOR(ClientContext, argument);
    }
    else if (!command.compare("DELE"))
    {
        this->HandleDELE(ClientContext, argument);
    }
    else if (!command.compare("ABOR"))
    {
        this->HandleABOR(ClientContext);
    }
    else if (!command.compare("PASV"))
    {
        this->HandlePASV(ClientContext);
    }
    else
    {
        std::cout << "Unsupported command: " << command << std::endl;
    }
}

_Use_decl_annotations_
bool
FTPServer::SendString(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Message)
{
    return this->SendString(ClientContext.Socket, Message);
}

_Use_decl_annotations_
bool
FTPServer::SendString(_In_ const SOCKET& Socket, _In_ const std::string& Message)
{
    return send(Socket, Message.c_str(), static_cast<int>(Message.size()), 0) != SOCKET_ERROR;
}

_Use_decl_annotations_
bool
FTPServer::HandleUSER(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    ClientContext.Access = CLIENT_ACCESS::NotLoggedIn;

    CHAR message[MESSAGE_MAX_LENGTH] = { 0 };
    _snprintf_s(message, sizeof(message), _TRUNCATE, "331 User %s OK. Password required\r\n", Argument.c_str());
    strcpy_s(ClientContext.UserName, Argument.c_str());
    return this->SendString(ClientContext, message);
}

_Use_decl_annotations_
bool
FTPServer::HandlePASS(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    const std::string& userName = ClientContext.UserName;
    if (!userName.starts_with(HARDCODED_USER) || !Argument.starts_with(HARDCODED_PASSWORD))
    {
        return this->SendString(ClientContext, "530 Invalid user name or password.\r\n");
    }

    ClientContext.Access = CLIENT_ACCESS::Full;
    return this->SendString(ClientContext, "230 User logged in\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleSYST(_In_ const CLIENT_CONTEXT& ClientContext)
{
    return this->SendString(ClientContext, "215 Windows_NT version 10.0\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleFEAT(_In_ const CLIENT_CONTEXT& ClientContext)
{
    return this->SendString(ClientContext, "211-Extensions supported:\r\n PASV\r\n UTF8\r\n211 End.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandlePWD(_In_ const CLIENT_CONTEXT& ClientContext)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    CHAR message[MESSAGE_MAX_LENGTH] = { 0 };
    _snprintf_s(message, sizeof(message), _TRUNCATE, "257 \"%s\" is a current directory.\r\n", ClientContext.CurrentDir);
    return this->SendString(ClientContext, message);
}

_Use_decl_annotations_
bool
FTPServer::HandleCWD(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (Argument.size() <= 1)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    if (Argument.contains("\\"))
    {
        strcpy_s(ClientContext.CurrentDir, Argument.c_str() + 1);
    }
    else
    {
        if (Argument.contains(".."))
        {
            PCCH lastSlash = strrchr(ClientContext.CurrentDir, '\\');
            if (lastSlash)
            {
                ClientContext.CurrentDir[lastSlash - ClientContext.CurrentDir] = ANSI_NULL;
            }
        }
        else
        {
            strcat_s(ClientContext.CurrentDir, "\\");
            strcat_s(ClientContext.CurrentDir, Argument.c_str());
        }
    }
    return this->SendString(ClientContext, "250 Requested file action okay, completed.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleTYPE(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    switch (Argument.c_str()[0])
    {
    case 'A':
    case 'a':
        return this->SendString(ClientContext, "200 Type set to A.\r\n");

    case 'I':
    case 'i':
        return this->SendString(ClientContext, "200 Type set to I.\r\n");

    default:
        return this->SendString(ClientContext, "501 Syntax error in parameters or argument.\r\n");
    }
}

_Use_decl_annotations_
bool
FTPServer::HandleLIST(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    WIN32_FIND_DATAA fileData = { 0 };
    HANDLE fileHandle = FindFirstFileA((std::string(ClientContext.CurrentDir) + "\\*").c_str(), &fileData);
    std::stringstream listStream;
    do
    {
        listStream << ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? "d" : "-")
            << "rw-r--r-- 1 owner group "
            << fileData.nFileSizeLow << " "
            << FiletimeToTimestamp(fileData.ftLastWriteTime) << " "
            << fileData.cFileName << "\r\n";
    } while (FindNextFileA(fileHandle, &fileData));
    FindClose(fileHandle);

    this->SendString(ClientContext, "150 Opening data connection.\r\n");

    //SOCKET dataSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //SOCKADDR_IN clientAddr = { .sin_family = AF_INET, .sin_port = ClientContext.DataPort, .sin_addr = ClientContext.DataIPv4 };
    //int status = connect(dataSocket, reinterpret_cast<PSOCKADDR>(&clientAddr), sizeof(clientAddr));
    //if (status == SOCKET_ERROR)
    //{
    //    return this->SendString(ClientContext, "550 File or directory unavailable.\r\n");
    //}

    SOCKET dataSocket = accept(ClientContext.DataSocket, NULL, NULL);
    closesocket(ClientContext.DataSocket);
    ClientContext.DataSocket = dataSocket;
    if (dataSocket == INVALID_SOCKET)
    {
        return false;
    }

    this->SendString(dataSocket, listStream.str());
    closesocket(dataSocket);
    return this->SendString(ClientContext, "226 Transfer complete.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandlePORT(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    int c;
    PCHAR p = const_cast<PCHAR>(Argument.c_str());
    ULONG dataAddr[4] = { 0UL };
    ULONG dataPort[2] = { 0UL };
    for (c = 0; c < 4; ++c)
    {
        dataAddr[c] = strtoul(p, &p, 10);
        if (*p != ',' && *p != 0)
        {
            break;
        }
        if (*p == 0)
        {
            return false;
        }
        ++p;
    }

    for (c = 0; c < 2; ++c)
    {
        dataPort[c] = strtoul(p, &p, 10);
        if (*p != ',' && *p != 0)
        {
            break;
        }
        if (*p == 0)
        {
            break;
        }
        ++p;
    }

    IN_ADDR dataIPv4 = { 0 };
    dataIPv4.S_un.S_un_b.s_b1 = static_cast<BYTE>(dataAddr[0]);
    dataIPv4.S_un.S_un_b.s_b2 = static_cast<BYTE>(dataAddr[1]);
    dataIPv4.S_un.S_un_b.s_b3 = static_cast<BYTE>(dataAddr[2]);
    dataIPv4.S_un.S_un_b.s_b4 = static_cast<BYTE>(dataAddr[3]);
    if (dataIPv4.S_un.S_addr != ClientContext.IPv4.S_un.S_addr)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    ClientContext.DataIPv4.S_un.S_addr = dataIPv4.S_un.S_addr;
    ClientContext.DataPort = static_cast<USHORT>((dataPort[1] << 8) + dataPort[0]);
    return this->SendString(ClientContext, "200 Transfer complete.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleREST(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    return this->SendString(ClientContext, "350 REST supported.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleQUIT(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    return this->SendString(ClientContext, "221 Quit.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleRETR(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    bool status = false;
    bool fileFound = false;
    WIN32_FIND_DATAA fileData = { 0 };
    HANDLE fileHandle = FindFirstFileA((std::string(ClientContext.CurrentDir) + "\\*").c_str(), &fileData);
    do
    {
        if (!strcmp(Argument.c_str(), fileData.cFileName))
        {
            this->SendString(ClientContext, "150 Opening data connection.\r\n");

            //SOCKET dataSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            //SOCKADDR_IN clientAddr = { .sin_family = AF_INET, .sin_port = ClientContext.DataPort, .sin_addr = ClientContext.DataIPv4 };
            //int status = connect(dataSocket, reinterpret_cast<PSOCKADDR>(&clientAddr), sizeof(clientAddr));
            //if (status == SOCKET_ERROR)
            //{
            //    return this->SendString(ClientContext, "550 File or directory unavailable.\r\n");
            //}

            SOCKET dataSocket = accept(ClientContext.DataSocket, NULL, NULL);
            closesocket(ClientContext.DataSocket);
            ClientContext.DataSocket = dataSocket;
            if (dataSocket == INVALID_SOCKET)
            {
                return false;
            }

            std::ifstream file(std::string(ClientContext.CurrentDir) + "\\" + fileData.cFileName, std::ios::binary);
            if (!file.is_open())
            {
                closesocket(dataSocket);
                return this->SendString(ClientContext, "550 File not found or access denied.\r\n");
            }

            char buffer[1024] = { 0 };
            while (file.read(buffer, sizeof(buffer)) || file.gcount())
            {
                if (send(dataSocket, buffer, static_cast<int>(file.gcount()), 0) == SOCKET_ERROR)
                {
                    file.close();
                    closesocket(dataSocket);
                    return this->SendString(ClientContext, "426 Connection closed; transfer aborted.\r\n");
                }
            }
            file.close();
            closesocket(dataSocket);
            status = this->SendString(ClientContext, "226 Transfer complete.\r\n");
            fileFound = true;

            break;
        }
    } while (FindNextFileA(fileHandle, &fileData));
    FindClose(fileHandle);

    if (!fileFound)
    {
        status = this->SendString(ClientContext, "550 File or directory unavailable.\r\n");
    }

    return status;
}

_Use_decl_annotations_
bool
FTPServer::HandleSTOR(_Inout_ CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (ClientContext.Access == CLIENT_ACCESS::ReadOnly)
    {
        return this->SendString(ClientContext, "550 Permission denied.\r\n");
    }

    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    std::ofstream file(std::string(ClientContext.CurrentDir) + "\\" + Argument, std::ios::binary);
    if (!file.is_open())
    {
        this->SendString(ClientContext, "550 Cannot open file for writing.\r\n");
        return false;
    }

    this->SendString(ClientContext, "150 Opening data connection.\r\n");

    //SOCKET dataSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //SOCKADDR_IN clientAddr = { .sin_family = AF_INET, .sin_port = ClientContext.DataPort, .sin_addr = ClientContext.DataIPv4 };
    //int status = connect(dataSocket, (PSOCKADDR)&clientAddr, sizeof(clientAddr));
    //if (status == SOCKET_ERROR)
    //{
    //    return this->SendString(ClientContext, "550 File or directory unavailable.\r\n");
    //}

    SOCKET dataSocket = accept(ClientContext.DataSocket, NULL, NULL);
    closesocket(ClientContext.DataSocket);
    ClientContext.DataSocket = dataSocket;
    if (dataSocket == INVALID_SOCKET)
    {
        return false;
    }

    int bytesRead;
    char buffer[1024] = { 0 };
    while ((bytesRead = recv(dataSocket, buffer, sizeof(buffer), 0)) > 0)
    {
        file.write(buffer, bytesRead);
    }

    file.close();
    closesocket(dataSocket);

    if (bytesRead < 0)
    {
        return this->SendString(ClientContext, "426 Connection closed; transfer aborted.\r\n");
    }

    return this->SendString(ClientContext, "226 Transfer complete.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandleDELE(_In_ const CLIENT_CONTEXT& ClientContext, _In_ const std::string& Argument)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    if (ClientContext.Access != CLIENT_ACCESS::Full)
    {
        return this->SendString(ClientContext, "550 Permission denied.\r\n");
    }

    if (Argument.size() == 0)
    {
        return this->SendString(ClientContext, "501 Syntax error in parameters or arguments.\r\n");
    }

    CHAR fullPath[MAX_PATH] = { 0 };
    strcpy_s(fullPath, Argument.c_str() + 1);
    if (std::remove(fullPath) != 0)
    {
        return this->SendString(ClientContext, "550 File or directory unavailable.\r\n");
    }
    else
    {
        return this->SendString(ClientContext, "250 Requested file action okay, completed.\r\n");
    }
}

_Use_decl_annotations_
bool
FTPServer::HandleABOR(_In_ const CLIENT_CONTEXT& ClientContext)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    return this->SendString(ClientContext, "226 Transfer complete. Closing data connection.\r\n");
}

_Use_decl_annotations_
bool
FTPServer::HandlePASV(_Inout_ CLIENT_CONTEXT& ClientContext)
{
    if (ClientContext.Access == CLIENT_ACCESS::NotLoggedIn)
    {
        return this->SendString(ClientContext, "530 Please login with USER and PASS.\r\n");
    }

    SOCKET passiveSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (passiveSocket == INVALID_SOCKET)
    {
        closesocket(passiveSocket);
        return this->SendString(ClientContext, "451 Requested action aborted. Local error in processing.\r\n");
    }

    SOCKADDR_IN serverAddr = { .sin_family = AF_INET, .sin_port = htons((rand() % 5000) + 60000), .sin_addr = ClientContext.IPv4 };
    int status = bind(passiveSocket, reinterpret_cast<PSOCKADDR>(&serverAddr), sizeof(serverAddr));
    if (status == SOCKET_ERROR)
    {
        closesocket(passiveSocket);
        return this->SendString(ClientContext, "451 Requested action aborted. Local error in processing.\r\n");
    }

    status = listen(passiveSocket, SOMAXCONN);
    if (status == SOCKET_ERROR)
    {
        closesocket(passiveSocket);
        return this->SendString(ClientContext, "451 Requested action aborted. Local error in processing.\r\n");
    }

    ClientContext.DataIPv4 = serverAddr.sin_addr;
    ClientContext.DataPort = serverAddr.sin_port;
    ClientContext.DataSocket = passiveSocket;

    CHAR message[MESSAGE_MAX_LENGTH] = { 0 };
    _snprintf_s(message, sizeof(message), _TRUNCATE,
        "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u).\r\n",
        ClientContext.DataIPv4.s_addr & 0xFF,
        (ClientContext.DataIPv4.s_addr >> 8) & 0xFF,
        (ClientContext.DataIPv4.s_addr >> 16) & 0xFF,
        (ClientContext.DataIPv4.s_addr >> 24) & 0xFF,
        ClientContext.DataPort & 0xFF,
        (ClientContext.DataPort >> 8) & 0xFF);
    return this->SendString(ClientContext, message);
}
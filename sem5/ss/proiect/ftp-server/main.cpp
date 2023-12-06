#include "pch.h"
#include "FTPServer.hpp"

int main()
{
    try
    {
        FTPServer server;
        server.Start();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what();
    }

    //// Shutdown the connection since we're done
    //iResult = shutdown(ClientSocket, SD_SEND);
    //if (iResult == SOCKET_ERROR) {
    //    std::cout << "shutdown failed: " << WSAGetLastError() << std::endl;
    //    closesocket(ClientSocket);
    //    WSACleanup();
    //    return 1;
    //}

    return 0;
}
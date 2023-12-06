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

    return 0;
}
#include "ServerWorker.hpp"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ServerWorker worker;

    return a.exec();
}
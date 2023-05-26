#include "ServerWorker.hpp"
#include <QtCore/QCoreApplication>
#include <QxOrm.h>
#include "UserRepository.hpp"
#include "UserDatabase.hpp"
#include "ActionDatabase.hpp"
#include "ServerService.hpp"

#pragma comment(lib, "QxOrmd.lib")
#pragma comment(lib, "domain.lib")

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName("./ninjeye.db");
    qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
    qx::QxSqlDatabase::getSingleton()->setUserName("root");
    qx::QxSqlDatabase::getSingleton()->setPassword("");
    qx::QxSqlDatabase::getSingleton()->setFormatSqlQueryBeforeLogging(true);
    qx::QxSqlDatabase::getSingleton()->setDisplayTimerDetails(true);
    qx::QxSqlDatabase::getSingleton()->setVerifyOffsetRelation(true);

    UserRepository* users = new UserDatabase();
    ActionRepository* actions = new ActionDatabase();
    IService* service = new ServerService(users, actions);

    ServerWorker worker(55002, service);

    return a.exec();
}
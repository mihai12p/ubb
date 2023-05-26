#include "LoginWindow.hpp"
#include <QtWidgets/QApplication>
#include <QxOrm.h>

#pragma comment(lib, "domain.lib")
#pragma comment(lib, "QxOrmd.lib")

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/Logo/icon.ico"));

    ClientWorker worker("localhost", 55002);
    ClientController controller(worker);

    LoginWindow loginWindow(controller);
    loginWindow.show();

    return a.exec();
}
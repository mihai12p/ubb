#include "LoginWindow.hpp"
#include <QtWidgets/qmessagebox.h>
#include "MainWindow.hpp"

LoginWindow::LoginWindow(ClientController& controller, QWidget* parent) : QMainWindow(parent), controller{ controller }
{
    ui.setupUi(this);

    connect(&this->controller.GetWorker().GetSocket(), &QAbstractSocket::errorOccurred, this, &LoginWindow::HandleError);
    connect(&this->controller.GetWorker(), &ClientWorker::errorOccurred, [&](const QString& error) { QMessageBox::critical(this, "Server Error", error); });
    connect(&this->controller.GetWorker(), &ClientWorker::continueLogin, this, &LoginWindow::continueLogin);
    connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::login);
}

void LoginWindow::HandleError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, "Error", "Connection has been refused");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::critical(this, "Error", "Remote host has closed the connection");
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, "Error", "Host address not found");
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::critical(this, "Error", "Connection timed out");
        break;
    default:
        QMessageBox::critical(this, "Error", tr("Unhandled error. Error code: %1").arg(socketError));
        break;
    }
}

void LoginWindow::login()
{
    this->controller.login(ui.usernameInput->text(), ui.passwordInput->text());
}

void LoginWindow::continueLogin()
{
    qInfo() << "Login succeeded...";

    this->hide();

    MainWindow* mainWindow = new MainWindow(this->controller);
    mainWindow->setWindowTitle("NinjEye for " + ui.usernameInput->text());
    mainWindow->show();
}
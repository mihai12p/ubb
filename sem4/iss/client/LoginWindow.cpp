#include "LoginWindow.hpp"
#include <QtWidgets/qmessagebox.h>

LoginWindow::LoginWindow(ClientController& controller, QWidget* parent) : QMainWindow(parent), controller{ controller }
{
    ui.setupUi(this);

    connect(&this->controller.GetSocket(), &QAbstractSocket::errorOccurred, this, &LoginWindow::HandleError);
    connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::Login);
}

void LoginWindow::HandleError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, "Error", "Connection has been refused");
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this, "Error", "Remote host has closed the connection");
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, "Error", "Host address not found");
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::information(this, "Error", "Connection timed out");
        break;
    default:
        QMessageBox::information(this, "Error", tr("Unhandled error. Error code: %1").arg(socketError));
        break;
    }
}

void LoginWindow::Login()
{
    this->controller.Login(ui.usernameInput->text(), ui.passwordInput->text());
}
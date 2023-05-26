#pragma once

#include <QtWidgets/QMainWindow>
#include <ui_LoginWindow.h>
#include "ClientController.hpp"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(ClientController& controller, QWidget *parent = nullptr);

private slots:
    void HandleError(QAbstractSocket::SocketError socketError);

    void login();
    void continueLogin();

private:
    Ui::LoginWindowClass ui;
    ClientController& controller;
};